#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Curl_multi {scalar_t__ in_callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxconnects; scalar_t__* errorbuffer; } ;
struct Curl_easy {struct Curl_multi* multi; TYPE_1__ set; struct Curl_multi* multi_easy; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_FAILED_INIT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_RECURSIVE_API_CALL ; 
 int /*<<< orphan*/  CURLMOPT_MAXCONNECTS ; 
 scalar_t__ CURLM_OUT_OF_MEMORY ; 
 struct Curl_multi* Curl_multi_handle (int,int) ; 
 int /*<<< orphan*/  SIGPIPE_VARIABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ curl_multi_add_handle (struct Curl_multi*,struct Curl_easy*) ; 
 int /*<<< orphan*/  curl_multi_cleanup (struct Curl_multi*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (struct Curl_multi*,struct Curl_easy*) ; 
 int /*<<< orphan*/  curl_multi_setopt (struct Curl_multi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  easy_events (struct Curl_multi*) ; 
 int /*<<< orphan*/  easy_transfer (struct Curl_multi*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  pipe_st ; 
 int /*<<< orphan*/  sigpipe_ignore (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe_restore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode easy_perform(struct Curl_easy *data, bool events)
{
  struct Curl_multi *multi;
  CURLMcode mcode;
  CURLcode result = CURLE_OK;
  SIGPIPE_VARIABLE(pipe_st);

  if(!data)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  if(data->set.errorbuffer)
    /* clear this as early as possible */
    data->set.errorbuffer[0] = 0;

  if(data->multi) {
    failf(data, "easy handle already used in multi handle");
    return CURLE_FAILED_INIT;
  }

  if(data->multi_easy)
    multi = data->multi_easy;
  else {
    /* this multi handle will only ever have a single easy handled attached
       to it, so make it use minimal hashes */
    multi = Curl_multi_handle(1, 3);
    if(!multi)
      return CURLE_OUT_OF_MEMORY;
    data->multi_easy = multi;
  }

  if(multi->in_callback)
    return CURLE_RECURSIVE_API_CALL;

  /* Copy the MAXCONNECTS option to the multi handle */
  curl_multi_setopt(multi, CURLMOPT_MAXCONNECTS, data->set.maxconnects);

  mcode = curl_multi_add_handle(multi, data);
  if(mcode) {
    curl_multi_cleanup(multi);
    if(mcode == CURLM_OUT_OF_MEMORY)
      return CURLE_OUT_OF_MEMORY;
    return CURLE_FAILED_INIT;
  }

  sigpipe_ignore(data, &pipe_st);

  /* assign this after curl_multi_add_handle() since that function checks for
     it and rejects this handle otherwise */
  data->multi = multi;

  /* run the transfer */
  result = events ? easy_events(multi) : easy_transfer(multi);

  /* ignoring the return code isn't nice, but atm we can't really handle
     a failure here, room for future improvement! */
  (void)curl_multi_remove_handle(multi, data);

  sigpipe_restore(&pipe_st);

  /* The multi handle is kept alive, owned by the easy handle */
  return result;
}