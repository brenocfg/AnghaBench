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
struct TYPE_2__ {int /*<<< orphan*/  p_mqueue; } ;
struct knote {TYPE_1__ kn_ptr; } ;
typedef  int /*<<< orphan*/  ipc_mqueue_t ;

/* Variables and functions */
 int FILTER_ACTIVE ; 
 scalar_t__ ipc_mqueue_set_peek (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_machportpeek(struct knote *kn)
{
	ipc_mqueue_t mqueue = kn->kn_ptr.p_mqueue;

	return ipc_mqueue_set_peek(mqueue) ? FILTER_ACTIVE : 0;
}