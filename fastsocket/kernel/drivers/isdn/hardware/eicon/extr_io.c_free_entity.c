#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
typedef  size_t byte ;
struct TYPE_7__ {scalar_t__ io; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_spin_lock; int /*<<< orphan*/  e_count; TYPE_1__* e_tbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * e; } ;
typedef  TYPE_2__* PISDN_ADAPTER ;
typedef  TYPE_3__ ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void free_entity(ADAPTER * a, byte e_no)
{
  PISDN_ADAPTER IoAdapter;
 diva_os_spin_lock_magic_t irql;
  IoAdapter = (PISDN_ADAPTER) a->io;
 diva_os_enter_spin_lock (&IoAdapter->data_spin_lock, &irql, "data_free");
  IoAdapter->e_tbl[e_no].e = NULL;
  IoAdapter->e_count--;
 diva_os_leave_spin_lock (&IoAdapter->data_spin_lock, &irql, "data_free");
}