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
 scalar_t__ CURLFTPMETHOD_NOCWD ; 
 scalar_t__ CURLFTPMETHOD_SINGLECWD ; 
 int /*<<< orphan*/  CURLOPT_FTP_FILEMETHOD ; 
 int /*<<< orphan*/  CURLOPT_QUOTE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 char* aprintf (char*,char*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
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
   CURL *curl;
   char *newURL = NULL;
   struct curl_slist *slist = NULL;

   if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
     fprintf(stderr, "curl_global_init() failed\n");
     return TEST_ERR_MAJOR_BAD;
   }

   curl = curl_easy_init();
   if(!curl) {
     fprintf(stderr, "curl_easy_init() failed\n");
     curl_global_cleanup();
     return TEST_ERR_MAJOR_BAD;
   }

   /*
    * Begin with curl set to use a single CWD to the URL's directory.
    */
   test_setopt(curl, CURLOPT_URL, URL);
   test_setopt(curl, CURLOPT_VERBOSE, 1L);
   test_setopt(curl, CURLOPT_FTP_FILEMETHOD, (long) CURLFTPMETHOD_SINGLECWD);

   res = curl_easy_perform(curl);

   /*
    * Change the FTP_FILEMETHOD option to use full paths rather than a CWD
    * command.  Alter the URL's path a bit, appending a "./".  Use an innocuous
    * QUOTE command, after which curl will CWD to ftp_conn->entrypath and then
    * (on the next call to ftp_statemach_act) find a non-zero ftpconn->dirdepth
    * even though no directories are stored in the ftpconn->dirs array (after a
    * call to freedirs).
    */
   newURL = aprintf("%s./", URL);
   if(newURL == NULL) {
     curl_easy_cleanup(curl);
     curl_global_cleanup();
     return TEST_ERR_MAJOR_BAD;
   }

   slist = curl_slist_append(NULL, "SYST");
   if(slist == NULL) {
     free(newURL);
     curl_easy_cleanup(curl);
     curl_global_cleanup();
     return TEST_ERR_MAJOR_BAD;
   }

   test_setopt(curl, CURLOPT_URL, newURL);
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