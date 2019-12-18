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
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLFTPMETHOD_NOCWD ; 
 scalar_t__ CURLFTPMETHOD_SINGLECWD ; 
 int /*<<< orphan*/  CURLOPT_FTP_FILEMETHOD ; 
 int /*<<< orphan*/  CURLOPT_IGNORE_CONTENT_LENGTH ; 
 int /*<<< orphan*/  CURLOPT_NOBODY ; 
 int /*<<< orphan*/  CURLOPT_QUOTE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 char* aprintf (char*,char*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 char* curl_slist_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
   CURLcode res;
   CURL *curl = NULL;
   char *newURL = NULL;
   struct curl_slist *slist = NULL;

   if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
     fprintf(stderr, "curl_global_init() failed\n");
     return TEST_ERR_MAJOR_BAD;
   }

   curl = curl_easy_init();
   if(!curl) {
     fprintf(stderr, "curl_easy_init() failed\n");
     res = TEST_ERR_MAJOR_BAD;
     goto test_cleanup;
   }

   /* test: CURLFTPMETHOD_SINGLECWD with absolute path should
            skip CWD to entry path */
   newURL = aprintf("%s/folderA/661", URL);
   test_setopt(curl, CURLOPT_URL, newURL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_SINGLECWD);
   res = curl_easy_perform(curl);

   free(newURL);
   newURL = aprintf("%s/folderB/661", URL);
   test_setopt(curl, CURLOPT_URL, newURL);
   res = curl_easy_perform(curl);

   /* test: CURLFTPMETHOD_NOCWD with absolute path should
      never emit CWD (for both new and reused easy handle) */
   curl_easy_cleanup(curl);
   curl = curl_easy_init();
   if(!curl) {
     fprintf(stderr, "curl_easy_init() failed\n");
     res = TEST_ERR_MAJOR_BAD;
     goto test_cleanup;
   }

   free(newURL);
   newURL = aprintf("%s/folderA/661", URL);
   test_setopt(curl, CURLOPT_URL, newURL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_NOCWD);
   res = curl_easy_perform(curl);

   /* curve ball: CWD /folderB before reusing connection with _NOCWD */
   free(newURL);
   newURL = aprintf("%s/folderB/661", URL);
   test_setopt(curl, CURLOPT_URL, newURL);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_SINGLECWD);
   res = curl_easy_perform(curl);

   free(newURL);
   newURL = aprintf("%s/folderA/661", URL);
   test_setopt(curl, CURLOPT_URL, newURL);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_NOCWD);
   res = curl_easy_perform(curl);

   /* test: CURLFTPMETHOD_NOCWD with home-relative path should
      not emit CWD for first FTP access after login */
   curl_easy_cleanup(curl);
   curl = curl_easy_init();
   if(!curl) {
     fprintf(stderr, "curl_easy_init() failed\n");
     res = TEST_ERR_MAJOR_BAD;
     goto test_cleanup;
   }

   slist = curl_slist_append(NULL, "SYST");
   if(slist == NULL) {
     fprintf(stderr, "curl_slist_append() failed\n");
     res = TEST_ERR_MAJOR_BAD;
     goto test_cleanup;
   }

   test_setopt(curl, CURLOPT_URL, URL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_NOBODY, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_NOCWD);
   test_setopt(curl, CURLOPT_QUOTE, slist);
   res = curl_easy_perform(curl);

   /* test: CURLFTPMETHOD_SINGLECWD with home-relative path should
      not emit CWD for first FTP access after login */
   curl_easy_cleanup(curl);
   curl = curl_easy_init();
   if(!curl) {
     fprintf(stderr, "curl_easy_init() failed\n");
     res = TEST_ERR_MAJOR_BAD;
     goto test_cleanup;
   }

   test_setopt(curl, CURLOPT_URL, URL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_NOBODY, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_SINGLECWD);
   test_setopt(curl, CURLOPT_QUOTE, slist);
   res = curl_easy_perform(curl);

   /* test: CURLFTPMETHOD_NOCWD with home-relative path should
      not emit CWD for second FTP access when not needed +
      bonus: see if path buffering survives curl_easy_reset() */
   curl_easy_reset(curl);
   test_setopt(curl, CURLOPT_URL, URL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_NOBODY, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_NOCWD);
   test_setopt(curl, CURLOPT_QUOTE, slist);
   res = curl_easy_perform(curl);


test_cleanup:

   curl_slist_free_all(slist);
   free(newURL);
   curl_easy_cleanup(curl);
   curl_global_cleanup();

   return (int)res;
}