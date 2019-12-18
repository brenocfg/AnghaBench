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
typedef  int /*<<< orphan*/  u32 ;
struct fritzcard {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_status (struct fritzcard*,int) ; 

void
clear_pending_hdlc_ints(struct fritzcard *fc)
{
	u32 val;

	val = read_status(fc, 1);
	pr_debug("%s: HDLC 1 STA %x\n", fc->name, val);
	val = read_status(fc, 2);
	pr_debug("%s: HDLC 2 STA %x\n", fc->name, val);
}