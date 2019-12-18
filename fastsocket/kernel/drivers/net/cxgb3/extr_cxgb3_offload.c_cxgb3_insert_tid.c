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
struct tid_info {int /*<<< orphan*/  tids_in_use; TYPE_1__* tid_tab; } ;
struct t3cdev {int dummy; } ;
struct cxgb3_client {int dummy; } ;
struct TYPE_4__ {struct tid_info tid_maps; } ;
struct TYPE_3__ {void* ctx; struct cxgb3_client* client; } ;

/* Variables and functions */
 TYPE_2__* T3C_DATA (struct t3cdev*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void cxgb3_insert_tid(struct t3cdev *tdev, struct cxgb3_client *client,
		      void *ctx, unsigned int tid)
{
	struct tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	t->tid_tab[tid].client = client;
	t->tid_tab[tid].ctx = ctx;
	atomic_inc(&t->tids_in_use);
}