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
struct curl_llist_element {struct connectdata* ptr; } ;
struct curl_hash_iterator {int dummy; } ;
struct curl_hash_element {struct connectbundle* ptr; } ;
struct connectdata {int dummy; } ;
struct TYPE_2__ {struct curl_llist_element* head; } ;
struct connectbundle {TYPE_1__ conn_list; } ;
struct conncache {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 struct curl_hash_element* Curl_hash_next_element (struct curl_hash_iterator*) ; 
 int /*<<< orphan*/  Curl_hash_start_iterate (int /*<<< orphan*/ *,struct curl_hash_iterator*) ; 

__attribute__((used)) static struct connectdata *
conncache_find_first_connection(struct conncache *connc)
{
  struct curl_hash_iterator iter;
  struct curl_hash_element *he;
  struct connectbundle *bundle;

  Curl_hash_start_iterate(&connc->hash, &iter);

  he = Curl_hash_next_element(&iter);
  while(he) {
    struct curl_llist_element *curr;
    bundle = he->ptr;

    curr = bundle->conn_list.head;
    if(curr) {
      return curr->ptr;
    }

    he = Curl_hash_next_element(&iter);
  }

  return NULL;
}