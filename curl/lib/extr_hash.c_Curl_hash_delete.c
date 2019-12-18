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
struct curl_llist_element {struct curl_hash_element* ptr; struct curl_llist_element* next; } ;
struct curl_llist {struct curl_llist_element* head; } ;
struct curl_hash_element {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct curl_hash {int /*<<< orphan*/  size; scalar_t__ (* comp_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,struct curl_llist_element*,void*) ; 
 struct curl_llist* FETCH_LIST (struct curl_hash*,void*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 

int Curl_hash_delete(struct curl_hash *h, void *key, size_t key_len)
{
  struct curl_llist_element *le;
  struct curl_llist *l = FETCH_LIST(h, key, key_len);

  for(le = l->head; le; le = le->next) {
    struct curl_hash_element *he = le->ptr;
    if(h->comp_func(he->key, he->key_len, key, key_len)) {
      Curl_llist_remove(l, le, (void *) h);
      --h->size;
      return 0;
    }
  }
  return 1;
}