#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pmem; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* clients ; 
 int /*<<< orphan*/  dbg_adapter_lock ; 
 int /*<<< orphan*/ * dbg_base ; 
 int /*<<< orphan*/  dbg_q_lock ; 
 int /*<<< orphan*/ * dbg_queue ; 
 int /*<<< orphan*/  diva_os_destroy_spin_lock (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ external_dbg_queue ; 

void* diva_maint_finit (void) {
  void* ret = (void*)dbg_base;
  int i;

  dbg_queue = NULL;
  dbg_base  = NULL;

  if (ret) {
    diva_os_destroy_spin_lock(&dbg_q_lock, "dbg_finit");
    diva_os_destroy_spin_lock(&dbg_adapter_lock, "dbg_finit");
  }

  if (external_dbg_queue) {
    ret = NULL;
  }
  external_dbg_queue = 0;

  for (i = 1; i < ARRAY_SIZE(clients); i++) {
    if (clients[i].pmem) {
      diva_os_free (0, clients[i].pmem);
    }
  }

  return (ret);
}