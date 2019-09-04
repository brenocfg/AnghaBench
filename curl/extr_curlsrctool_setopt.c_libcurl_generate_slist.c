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
struct curl_slist {int /*<<< orphan*/  data; struct curl_slist* next; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAN1 (char*,int) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  DATA1 (char*,int) ; 
 int /*<<< orphan*/  DATA3 (char*,int,int,char*) ; 
 int /*<<< orphan*/  DECL1 (char*,int) ; 
 char* c_escape (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int easysrc_slist_count ; 

__attribute__((used)) static CURLcode libcurl_generate_slist(struct curl_slist *slist, int *slistno)
{
  CURLcode ret = CURLE_OK;
  char *escaped = NULL;

  /* May need several slist variables, so invent name */
  *slistno = ++easysrc_slist_count;

  DECL1("struct curl_slist *slist%d;", *slistno);
  DATA1("slist%d = NULL;", *slistno);
  CLEAN1("curl_slist_free_all(slist%d);", *slistno);
  CLEAN1("slist%d = NULL;", *slistno);
  for(; slist; slist = slist->next) {
    Curl_safefree(escaped);
    escaped = c_escape(slist->data, CURL_ZERO_TERMINATED);
    if(!escaped)
      return CURLE_OUT_OF_MEMORY;
    DATA3("slist%d = curl_slist_append(slist%d, \"%s\");",
                                       *slistno, *slistno, escaped);
  }

 nomem:
  Curl_safefree(escaped);
  return ret;
}