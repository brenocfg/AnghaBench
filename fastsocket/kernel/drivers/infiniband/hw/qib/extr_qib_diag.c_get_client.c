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
struct qib_diag_client {int /*<<< orphan*/  state; int /*<<< orphan*/  pid; struct qib_devdata* dd; struct qib_diag_client* next; } ;
struct qib_devdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPENED ; 
 struct qib_diag_client* client_pool ; 
 TYPE_1__* current ; 
 struct qib_diag_client* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qib_diag_client *get_client(struct qib_devdata *dd)
{
	struct qib_diag_client *dc;

	dc = client_pool;
	if (dc)
		/* got from pool remove it and use */
		client_pool = dc->next;
	else
		/* None in pool, alloc and init */
		dc = kmalloc(sizeof *dc, GFP_KERNEL);

	if (dc) {
		dc->next = NULL;
		dc->dd = dd;
		dc->pid = current->pid;
		dc->state = OPENED;
	}
	return dc;
}