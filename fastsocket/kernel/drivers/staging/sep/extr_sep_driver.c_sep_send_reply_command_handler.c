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
struct sep_device {int /*<<< orphan*/  reply_ct; int /*<<< orphan*/  send_ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_HOST_HOST_SEP_GPR2_REG_ADDR ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sep_dump_message (struct sep_device*) ; 
 int /*<<< orphan*/  sep_mutex ; 
 int /*<<< orphan*/  sep_write_reg (struct sep_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sep_send_reply_command_handler(struct sep_device *sep)
{
	dbg("sep:sep_send_reply_command_handler start\n");

	/* flash cache */
	flush_cache_all();

	sep_dump_message(sep);

	mutex_lock(&sep_mutex);
	sep->send_ct++;  	/* update counter */
	/* send the interrupt to SEP */
	sep_write_reg(sep, HW_HOST_HOST_SEP_GPR2_REG_ADDR, sep->send_ct);
	/* update both counters */
	sep->send_ct++;
	sep->reply_ct++;
	mutex_unlock(&sep_mutex);
	dbg("sep: sep_send_reply_command_handler end\n");
}