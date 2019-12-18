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
struct slist_wc {struct curl_slist* last; struct curl_slist* first; } ;
struct curl_slist {struct curl_slist* next; } ;

/* Variables and functions */
 struct curl_slist* curl_slist_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 struct slist_wc* malloc (int) ; 

struct slist_wc *slist_wc_append(struct slist_wc *list,
                                 const char *data)
{
  struct curl_slist *new_item = curl_slist_append(NULL, data);

  if(!new_item)
    return NULL;

  if(!list) {
    list = malloc(sizeof(struct slist_wc));

    if(!list) {
      curl_slist_free_all(new_item);
      return NULL;
    }

    list->first = new_item;
    list->last = new_item;
    return list;
  }

  list->last->next = new_item;
  list->last = list->last->next;
  return list;
}