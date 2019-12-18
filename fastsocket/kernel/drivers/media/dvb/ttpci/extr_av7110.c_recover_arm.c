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
struct av7110 {int /*<<< orphan*/  (* recover ) (struct av7110*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_bootarm (struct av7110*) ; 
 int /*<<< orphan*/  av7110_check_ir_config (struct av7110*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  init_av7110_av (struct av7110*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  restart_feeds (struct av7110*) ; 
 int /*<<< orphan*/  stub1 (struct av7110*) ; 

__attribute__((used)) static void recover_arm(struct av7110 *av7110)
{
	dprintk(4, "%p\n",av7110);

	av7110_bootarm(av7110);
	msleep(100);

	init_av7110_av(av7110);

	/* card-specific recovery */
	if (av7110->recover)
		av7110->recover(av7110);

	restart_feeds(av7110);

#if defined(CONFIG_INPUT_EVDEV) || defined(CONFIG_INPUT_EVDEV_MODULE)
	av7110_check_ir_config(av7110, true);
#endif
}