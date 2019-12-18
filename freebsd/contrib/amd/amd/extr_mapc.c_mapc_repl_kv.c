#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** kvhash; } ;
typedef  TYPE_1__ mnt_map ;
struct TYPE_6__ {char* val; struct TYPE_6__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ kv ;

/* Variables and functions */
 int /*<<< orphan*/  FSTREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 size_t kvhash_of (char*) ; 
 int /*<<< orphan*/  mapc_add_kv (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static void
mapc_repl_kv(mnt_map *m, char *key, char *val)
{
  kv *k;

  /*
   * Compute the hash table offset
   */
  k = m->kvhash[kvhash_of(key)];

  /*
   * Scan the linked list for the key
   */
  while (k && !FSTREQ(k->key, key))
    k = k->next;

  if (k) {
    XFREE(k->val);
    k->val = val;
  } else {
    mapc_add_kv(m, key, val);
  }
}