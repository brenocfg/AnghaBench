#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* val; struct TYPE_4__* key; struct TYPE_4__* next; } ;
typedef  TYPE_1__ kv ;

/* Variables and functions */
 int NKVHASH ; 
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 

__attribute__((used)) static void
mapc_clear_kvhash(kv **kvhash)
{
  int i;

  /*
   * For each of the hash slots, chain
   * along free'ing the data.
   */
  for (i = 0; i < NKVHASH; i++) {
    kv *k = kvhash[i];
    while (k) {
      kv *n = k->next;
      XFREE(k->key);
      XFREE(k->val);
      XFREE(k);
      k = n;
    }
  }
}