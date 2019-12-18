#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int msg; int /*<<< orphan*/ * easy_handle; } ;
typedef  char FILE ;
typedef  TYPE_1__ CURLMsg ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_EFFECTIVE_URL ; 
 int /*<<< orphan*/  CURLINFO_PRIVATE ; 
#define  CURLMSG_DONE 128 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  curl_handle ; 
 TYPE_1__* curl_multi_info_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void check_multi_info(void)
{
  char *done_url;
  CURLMsg *message;
  int pending;
  CURL *easy_handle;
  FILE *file;

  while((message = curl_multi_info_read(curl_handle, &pending))) {
    switch(message->msg) {
    case CURLMSG_DONE:
      /* Do not use message data after calling curl_multi_remove_handle() and
         curl_easy_cleanup(). As per curl_multi_info_read() docs:
         "WARNING: The data the returned pointer points to will not survive
         calling curl_multi_cleanup, curl_multi_remove_handle or
         curl_easy_cleanup." */
      easy_handle = message->easy_handle;

      curl_easy_getinfo(easy_handle, CURLINFO_EFFECTIVE_URL, &done_url);
      curl_easy_getinfo(easy_handle, CURLINFO_PRIVATE, &file);
      printf("%s DONE\n", done_url);

      curl_multi_remove_handle(curl_handle, easy_handle);
      curl_easy_cleanup(easy_handle);
      if(file) {
        fclose(file);
      }
      break;

    default:
      fprintf(stderr, "CURLMSG default\n");
      break;
    }
  }
}