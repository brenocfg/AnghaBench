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
 int known_regb ; 
 int /*<<< orphan*/  tr_flush_dirty_pr (int) ; 

__attribute__((used)) static void tr_release_pr(int r)
{
	tr_flush_dirty_pr(r);
	known_regb &= ~(1 << (r+8));
}