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
struct curl_hash {int slots; scalar_t__ size; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 

void
Curl_hash_destroy(struct curl_hash *h)
{
  int i;

  for(i = 0; i < h->slots; ++i) {
    Curl_llist_destroy(&h->table[i], (void *) h);
  }

  Curl_safefree(h->table);
  h->size = 0;
  h->slots = 0;
}