#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct curl_hash_iterator {int slot_index; TYPE_2__* current_element; struct curl_hash* hash; } ;
struct curl_hash_element {int dummy; } ;
struct curl_hash {int slots; TYPE_1__* table; } ;
struct TYPE_4__ {struct curl_hash_element* ptr; struct TYPE_4__* next; } ;
struct TYPE_3__ {TYPE_2__* head; } ;

/* Variables and functions */

struct curl_hash_element *
Curl_hash_next_element(struct curl_hash_iterator *iter)
{
  struct curl_hash *h = iter->hash;

  /* Get the next element in the current list, if any */
  if(iter->current_element)
    iter->current_element = iter->current_element->next;

  /* If we have reached the end of the list, find the next one */
  if(!iter->current_element) {
    int i;
    for(i = iter->slot_index; i < h->slots; i++) {
      if(h->table[i].head) {
        iter->current_element = h->table[i].head;
        iter->slot_index = i + 1;
        break;
      }
    }
  }

  if(iter->current_element) {
    struct curl_hash_element *he = iter->current_element->ptr;
    return he;
  }
  iter->current_element = NULL;
  return NULL;
}