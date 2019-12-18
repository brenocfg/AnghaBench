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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jprobe_return () ; 
 int /*<<< orphan*/  lkdtm_handler () ; 

__attribute__((used)) static void jp_ll_rw_block(int rw, int nr, struct buffer_head *bhs[])
{
	lkdtm_handler();
	jprobe_return();
}