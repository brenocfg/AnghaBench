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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  kevent_ast_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_KEVENT ; 
 int /*<<< orphan*/  act_set_ast_async (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_or (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
act_set_astkevent(thread_t thread, uint16_t bits)
{
	atomic_fetch_or(&thread->kevent_ast_bits, bits);

	/* kevent AST shouldn't send immediate IPIs */
	act_set_ast_async(thread, AST_KEVENT);
}