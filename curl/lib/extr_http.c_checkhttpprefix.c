#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {char* data; struct curl_slist* next; } ;
struct TYPE_2__ {struct curl_slist* http200aliases; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  scalar_t__ statusline ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_convert_from_network (struct Curl_easy*,char*,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ STATUS_BAD ; 
 scalar_t__ STATUS_DONE ; 
 scalar_t__ STATUS_UNKNOWN ; 
 scalar_t__ checkprefixmax (char*,char const*,size_t) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static statusline
checkhttpprefix(struct Curl_easy *data,
                const char *s, size_t len)
{
  struct curl_slist *head = data->set.http200aliases;
  statusline rc = STATUS_BAD;
  statusline onmatch = len >= 5? STATUS_DONE : STATUS_UNKNOWN;
#ifdef CURL_DOES_CONVERSIONS
  /* convert from the network encoding using a scratch area */
  char *scratch = strdup(s);
  if(NULL == scratch) {
    failf(data, "Failed to allocate memory for conversion!");
    return FALSE; /* can't return CURLE_OUT_OF_MEMORY so return FALSE */
  }
  if(CURLE_OK != Curl_convert_from_network(data, scratch, strlen(s) + 1)) {
    /* Curl_convert_from_network calls failf if unsuccessful */
    free(scratch);
    return FALSE; /* can't return CURLE_foobar so return FALSE */
  }
  s = scratch;
#endif /* CURL_DOES_CONVERSIONS */

  while(head) {
    if(checkprefixmax(head->data, s, len)) {
      rc = onmatch;
      break;
    }
    head = head->next;
  }

  if((rc != STATUS_DONE) && (checkprefixmax("HTTP/", s, len)))
    rc = onmatch;

#ifdef CURL_DOES_CONVERSIONS
  free(scratch);
#endif /* CURL_DOES_CONVERSIONS */
  return rc;
}