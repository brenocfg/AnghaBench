#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  curl; int /*<<< orphan*/  file; } ;
struct TYPE_7__ {scalar_t__ buffer_pos; TYPE_1__ handle; int /*<<< orphan*/  still_running; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ URL_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CFTYPE_CURL ; 
 int /*<<< orphan*/  CFTYPE_FILE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_multi_add_handle (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_perform (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char const*,char const*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ multi_handle ; 
 long write_callback ; 

URL_FILE *url_fopen(const char *url, const char *operation)
{
  /* this code could check for URLs or types in the 'url' and
     basically use the real fopen() for standard files */

  URL_FILE *file;
  (void)operation;

  file = calloc(1, sizeof(URL_FILE));
  if(!file)
    return NULL;

  file->handle.file = fopen(url, operation);
  if(file->handle.file)
    file->type = CFTYPE_FILE; /* marked as URL */

  else {
    file->type = CFTYPE_CURL; /* marked as URL */
    file->handle.curl = curl_easy_init();

    curl_easy_setopt(file->handle.curl, CURLOPT_URL, url);
    curl_easy_setopt(file->handle.curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(file->handle.curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(file->handle.curl, CURLOPT_WRITEFUNCTION, write_callback);

    if(!multi_handle)
      multi_handle = curl_multi_init();

    curl_multi_add_handle(multi_handle, file->handle.curl);

    /* lets start the fetch */
    curl_multi_perform(multi_handle, &file->still_running);

    if((file->buffer_pos == 0) && (!file->still_running)) {
      /* if still_running is 0 now, we should return NULL */

      /* make sure the easy handle is not in the multi handle anymore */
      curl_multi_remove_handle(multi_handle, file->handle.curl);

      /* cleanup */
      curl_easy_cleanup(file->handle.curl);

      free(file);

      file = NULL;
    }
  }
  return file;
}