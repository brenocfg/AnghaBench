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
struct netfs_trans {TYPE_1__* eng; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct netfs_trans*) ; 
 int /*<<< orphan*/  pohmelfs_crypto_thread_make_ready (int /*<<< orphan*/ ) ; 

void netfs_trans_free(struct netfs_trans *t)
{
	if (t->eng)
		pohmelfs_crypto_thread_make_ready(t->eng->thread);
	kfree(t);
}