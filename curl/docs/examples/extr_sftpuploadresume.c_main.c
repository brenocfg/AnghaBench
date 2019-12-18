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
 char* curl_version () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sftpResumeUpload (int /*<<< orphan*/ *,char const*,char const*) ; 

int main(void)
{
  const char *remote = "sftp://user:pass@example.com/path/filename";
  const char *filename = "filename";
  CURL *curlhandle = NULL;

  curl_global_init(CURL_GLOBAL_ALL);
  curlhandle = curl_easy_init();

  if(!sftpResumeUpload(curlhandle, remote, filename)) {
    printf("resumed upload using curl %s failed\n", curl_version());
  }

  curl_easy_cleanup(curlhandle);
  curl_global_cleanup();

  return 0;
}