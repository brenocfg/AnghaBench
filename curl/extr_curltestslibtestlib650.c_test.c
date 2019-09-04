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
struct curl_slist {int dummy; } ;
struct curl_httppost {int dummy; } ;
struct curl_forms {char* value; int /*<<< orphan*/  option; } ;
typedef  int /*<<< orphan*/  flbuf ;
typedef  int CURLcode ;
typedef  scalar_t__ CURLFORMcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLFORM_ARRAY ; 
 int /*<<< orphan*/  CURLFORM_CONTENTHEADER ; 
 int /*<<< orphan*/  CURLFORM_CONTENTSLENGTH ; 
 int /*<<< orphan*/  CURLFORM_CONTENTTYPE ; 
 int /*<<< orphan*/  CURLFORM_COPYCONTENTS ; 
 int /*<<< orphan*/  CURLFORM_COPYNAME ; 
 int /*<<< orphan*/  CURLFORM_END ; 
 int /*<<< orphan*/  CURLFORM_FILE ; 
 int /*<<< orphan*/  CURLFORM_FILECONTENT ; 
 int /*<<< orphan*/  CURLFORM_FILENAME ; 
 int /*<<< orphan*/  CURLFORM_NAMELENGTH ; 
 int /*<<< orphan*/  CURLFORM_PTRCONTENTS ; 
 int /*<<< orphan*/  CURLFORM_PTRNAME ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HTTPPOST ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  count_chars ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_formadd (struct curl_httppost**,struct curl_httppost**,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_formfree (struct curl_httppost*) ; 
 int /*<<< orphan*/  curl_formget (struct curl_httppost*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_msnprintf (char*,int,char*,unsigned long) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 char* data ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* libtest_arg2 ; 
 char* name ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURL *curl = NULL;
  CURLcode res = TEST_ERR_MAJOR_BAD;
  CURLFORMcode formrc;
  struct curl_slist *headers, *headers2 = NULL;
  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_forms formarray[3];
  size_t formlength = 0;
  char flbuf[32];
  long contentlength = 0;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* Check proper name and data copying, as well as headers. */
  headers = curl_slist_append(NULL, "X-customheader-1: Header 1 data");
  if(!headers) {
    goto test_cleanup;
  }
  headers2 = curl_slist_append(headers, "X-customheader-2: Header 2 data");
  if(!headers2) {
    goto test_cleanup;
  }
  headers = headers2;
  headers2 = curl_slist_append(headers, "Content-Type: text/plain");
  if(!headers2) {
    goto test_cleanup;
  }
  headers = headers2;
  formrc = curl_formadd(&formpost, &lastptr,
                        CURLFORM_COPYNAME, &name,
                        CURLFORM_COPYCONTENTS, &data,
                        CURLFORM_CONTENTHEADER, headers,
                        CURLFORM_END);

  if(formrc) {
    printf("curl_formadd(1) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  contentlength = (long)(strlen(data) - 1);

  /* Use a form array for the non-copy test. */
  formarray[0].option = CURLFORM_PTRCONTENTS;
  formarray[0].value = data;
  formarray[1].option = CURLFORM_CONTENTSLENGTH;
  formarray[1].value = (char *)(size_t)contentlength;
  formarray[2].option = CURLFORM_END;
  formarray[2].value = NULL;
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_PTRNAME, name,
                        CURLFORM_NAMELENGTH, strlen(name) - 1,
                        CURLFORM_ARRAY, formarray,
                        CURLFORM_FILENAME, "remotefile.txt",
                        CURLFORM_END);

  if(formrc) {
    printf("curl_formadd(2) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  /* Now change in-memory data to affect CURLOPT_PTRCONTENTS value.
     Copied values (first field) must not be affected.
     CURLOPT_PTRNAME actually copies the name thus we do not test this here. */
  data[0]++;

  /* Check multi-files and content type propagation. */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "multifile",
                        CURLFORM_FILE, libtest_arg2,    /* Set in first.c. */
                        CURLFORM_FILE, libtest_arg2,
                        CURLFORM_CONTENTTYPE, "text/whatever",
                        CURLFORM_FILE, libtest_arg2,
                        CURLFORM_END);

  if(formrc) {
    printf("curl_formadd(3) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  /* Check data from file content. */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "filecontents",
                        CURLFORM_FILECONTENT, libtest_arg2,
                        CURLFORM_END);

  if(formrc) {
    printf("curl_formadd(4) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  /* Measure the current form length.
   * This is done before including stdin data because we want to reuse it
   * and stdin cannot be rewound.
   */
  curl_formget(formpost, (void *) &formlength, count_chars);

  /* Include length in data for external check. */
  curl_msnprintf(flbuf, sizeof(flbuf), "%lu", (unsigned long) formlength);
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "formlength",
                        CURLFORM_COPYCONTENTS, &flbuf,
                        CURLFORM_END);
  if(formrc) {
    printf("curl_formadd(5) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  /* Check stdin (may be problematic on some platforms). */
  formrc = curl_formadd(&formpost,
                        &lastptr,
                        CURLFORM_COPYNAME, "standardinput",
                        CURLFORM_FILE, "-",
                        CURLFORM_END);
  if(formrc) {
    printf("curl_formadd(6) = %d\n", (int) formrc);
    goto test_cleanup;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    goto test_cleanup;
  }

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

  /* send a multi-part formpost */
  test_setopt(curl, CURLOPT_HTTPPOST, formpost);

  /* get verbose debug output please */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(curl, CURLOPT_HEADER, 1L);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);

  /* now cleanup the formpost chain */
  curl_formfree(formpost);
  curl_slist_free_all(headers);

  curl_global_cleanup();

  return res;
}