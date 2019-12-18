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
struct curl_slist {char* data; struct curl_slist* next; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_SSL_ENGINES ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct curl_slist**) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

void tool_list_engines(void)
{
  CURL *curl = curl_easy_init();
  struct curl_slist *engines = NULL;

  /* Get the list of engines */
  curl_easy_getinfo(curl, CURLINFO_SSL_ENGINES, &engines);

  puts("Build-time engines:");
  if(engines) {
    for(; engines; engines = engines->next)
      printf("  %s\n", engines->data);
  }
  else {
    puts("  <none>");
  }

  /* Cleanup the list of engines */
  curl_slist_free_all(engines);
  curl_easy_cleanup(curl);
}