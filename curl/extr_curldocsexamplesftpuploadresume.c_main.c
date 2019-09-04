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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upload (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int) ; 

int main(void)
{
  CURL *curlhandle = NULL;

  curl_global_init(CURL_GLOBAL_ALL);
  curlhandle = curl_easy_init();

  upload(curlhandle, "ftp://user:pass@example.com/path/file", "C:\\file",
         0, 3);

  curl_easy_cleanup(curlhandle);
  curl_global_cleanup();

  return 0;
}