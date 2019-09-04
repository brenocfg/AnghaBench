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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  block_hint_t ;
struct TYPE_3__ {int /*<<< orphan*/  pending_block_hint; } ;

/* Variables and functions */

void thread_set_pending_block_hint(thread_t thread, block_hint_t block_hint) {
	thread->pending_block_hint = block_hint;
}