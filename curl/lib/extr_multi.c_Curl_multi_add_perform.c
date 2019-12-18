#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {int dummy; } ;
struct SingleRequest {int /*<<< orphan*/  keepon; } ;
struct Curl_multi {scalar_t__ in_callback; } ;
struct Curl_easy {struct SingleRequest req; } ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 int /*<<< orphan*/  CURLM_STATE_PERFORM ; 
 int /*<<< orphan*/  Curl_attach_connnection (struct Curl_easy*,struct connectdata*) ; 
 int /*<<< orphan*/  Curl_init_do (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEEP_RECV ; 
 int /*<<< orphan*/  curl_multi_add_handle (struct Curl_multi*,struct Curl_easy*) ; 
 int /*<<< orphan*/  multistate (struct Curl_easy*,int /*<<< orphan*/ ) ; 

CURLMcode Curl_multi_add_perform(struct Curl_multi *multi,
                                 struct Curl_easy *data,
                                 struct connectdata *conn)
{
  CURLMcode rc;

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  rc = curl_multi_add_handle(multi, data);
  if(!rc) {
    struct SingleRequest *k = &data->req;

    /* pass in NULL for 'conn' here since we don't want to init the
       connection, only this transfer */
    Curl_init_do(data, NULL);

    /* take this handle to the perform state right away */
    multistate(data, CURLM_STATE_PERFORM);
    Curl_attach_connnection(data, conn);
    k->keepon |= KEEP_RECV; /* setup to receive! */
  }
  return rc;
}