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
struct initurl {long url; long share; int threadno; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_SHARE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int URL_ITERATIONS ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 long write_db ; 

__attribute__((used)) static void *run_thread(void *ptr)
{
  struct initurl *u = (struct initurl *)ptr;
  int i;

  for(i = 0; i < URL_ITERATIONS; i++) {
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, u->url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_SHARE, u->share);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_db);
    curl_easy_perform(curl); /* ignores error */
    curl_easy_cleanup(curl);
    fprintf(stderr, "Thread %d transfer %d\n", u->threadno, i);
  }

  return NULL;
}