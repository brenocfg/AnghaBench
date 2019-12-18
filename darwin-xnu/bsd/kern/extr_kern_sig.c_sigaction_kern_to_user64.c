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
struct TYPE_3__ {int /*<<< orphan*/  __sa_handler; } ;
struct user64_sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; TYPE_1__ __sigaction_u; } ;
struct TYPE_4__ {int /*<<< orphan*/  __sa_handler; } ;
struct kern_sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; TYPE_2__ __sigaction_u; } ;

/* Variables and functions */

__attribute__((used)) static void
sigaction_kern_to_user64(struct kern_sigaction *in, struct user64_sigaction *out)
{
	/* This assumes 32 bit __sa_handler is of type sig_t */
	out->__sigaction_u.__sa_handler = in->__sigaction_u.__sa_handler;
	out->sa_mask = in->sa_mask;
	out->sa_flags = in->sa_flags;
}