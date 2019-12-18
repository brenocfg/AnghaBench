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
typedef  char curl_slist ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_RESOLVE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* curl_slist_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 

int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  /* Each single name resolve string should be written using the format
     HOST:PORT:ADDRESS where HOST is the name libcurl will try to resolve,
     PORT is the port number of the service where libcurl wants to connect to
     the HOST and ADDRESS is the numerical IP address
   */
  struct curl_slist *host = curl_slist_append(NULL,
                                              "example.com:443:127.0.0.1");

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_RESOLVE, host);
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_slist_free_all(host);

  return (int)res;
}