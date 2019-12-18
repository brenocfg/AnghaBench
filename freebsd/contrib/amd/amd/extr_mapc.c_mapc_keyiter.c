#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_4__ {TYPE_2__** kvhash; } ;
typedef  TYPE_1__ mnt_map ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ kv ;
typedef  int /*<<< orphan*/  (* key_fun ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int NKVHASH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mapc_keyiter(mnt_map *m, key_fun *fn, opaque_t arg)
{
  int i;
  int c = 0;

  for (i = 0; i < NKVHASH; i++) {
    kv *k = m->kvhash[i];
    while (k) {
      (*fn) (k->key, arg);
      k = k->next;
      c++;
    }
  }

  return c;
}