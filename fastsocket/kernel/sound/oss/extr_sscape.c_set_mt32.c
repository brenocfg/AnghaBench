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
struct sscape_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMD_ACK ; 
 int /*<<< orphan*/  CMD_SET_MT32 ; 
 int /*<<< orphan*/  host_close (struct sscape_info*) ; 
 int /*<<< orphan*/  host_command2 (struct sscape_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host_open (struct sscape_info*) ; 
 scalar_t__ host_read (struct sscape_info*) ; 

__attribute__((used)) static void set_mt32(struct sscape_info *devc, int value)
{
	host_open(devc);
	host_command2(devc, CMD_SET_MT32, value ? 1 : 0);
	if (host_read(devc) != CMD_ACK)
	{
		/* printk( "SNDSCAPE: Setting MT32 mode failed\n"); */
	}
	host_close(devc);
}