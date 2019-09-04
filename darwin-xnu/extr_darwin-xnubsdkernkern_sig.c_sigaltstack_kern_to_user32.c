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
struct user32_sigaltstack {int /*<<< orphan*/  ss_flags; void* ss_size; void* ss_sp; } ;
struct kern_sigaltstack {int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;

/* Variables and functions */
 void* CAST_DOWN_EXPLICIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user32_addr_t ; 
 int /*<<< orphan*/  user32_size_t ; 

__attribute__((used)) static void
sigaltstack_kern_to_user32(struct kern_sigaltstack *in, struct user32_sigaltstack *out)
{
	out->ss_sp	    = CAST_DOWN_EXPLICIT(user32_addr_t, in->ss_sp);
	out->ss_size	= CAST_DOWN_EXPLICIT(user32_size_t, in->ss_size);
	out->ss_flags	= in->ss_flags;
}