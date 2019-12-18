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
struct vmballoon {int reset_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  vmballoon_pop (struct vmballoon*) ; 
 int /*<<< orphan*/  vmballoon_send_guest_id (struct vmballoon*) ; 
 scalar_t__ vmballoon_send_start (struct vmballoon*) ; 

__attribute__((used)) static void vmballoon_reset(struct vmballoon *b)
{
	/* free all pages, skipping monitor unlock */
	vmballoon_pop(b);

	if (vmballoon_send_start(b)) {
		b->reset_required = false;
		if (!vmballoon_send_guest_id(b))
			pr_err("failed to send guest ID to the host\n");
	}
}