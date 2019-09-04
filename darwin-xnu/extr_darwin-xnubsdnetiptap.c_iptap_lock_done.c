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

/* Variables and functions */
 int /*<<< orphan*/  iptap_lck_rw ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iptap_lock_done(void)
{
	lck_rw_done(&iptap_lck_rw);
}