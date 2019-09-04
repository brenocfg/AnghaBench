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
struct curl_llist_element {struct curl_llist_element* next; struct curl_hash_element* ptr; } ;
struct curl_llist {struct curl_llist_element* head; } ;
struct curl_hash_element {void* ptr; } ;
struct curl_hash {int slots; int /*<<< orphan*/  size; struct curl_llist* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,struct curl_llist_element*,void*) ; 

void
Curl_hash_clean_with_criterium(struct curl_hash *h, void *user,
                               int (*comp)(void *, void *))
{
  struct curl_llist_element *le;
  struct curl_llist_element *lnext;
  struct curl_llist *list;
  int i;

  if(!h)
    return;

  for(i = 0; i < h->slots; ++i) {
    list = &h->table[i];
    le = list->head; /* get first list entry */
    while(le) {
      struct curl_hash_element *he = le->ptr;
      lnext = le->next;
      /* ask the callback function if we shall remove this entry or not */
      if(comp == NULL || comp(user, he->ptr)) {
        Curl_llist_remove(list, le, (void *) h);
        --h->size; /* one less entry in the hash now */
      }
      le = lnext;
    }
  }
}