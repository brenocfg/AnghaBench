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
struct curl_slist {struct curl_slist* next; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct curl_slist* curl_slist_append (struct curl_slist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 

struct curl_slist *Curl_slist_duplicate(struct curl_slist *inlist)
{
  struct curl_slist *outlist = NULL;
  struct curl_slist *tmp;

  while(inlist) {
    tmp = curl_slist_append(outlist, inlist->data);

    if(!tmp) {
      curl_slist_free_all(outlist);
      return NULL;
    }

    outlist = tmp;
    inlist = inlist->next;
  }
  return outlist;
}