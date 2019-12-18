#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct user64_sigaltstack {int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
struct kern_sigaltstack {int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;

/* Variables and functions */

__attribute__((used)) static void
sigaltstack_kern_to_user64(struct kern_sigaltstack *in, struct user64_sigaltstack *out)
{
	out->ss_sp	    = in->ss_sp;
	out->ss_size	= in->ss_size;
	out->ss_flags	= in->ss_flags;
}