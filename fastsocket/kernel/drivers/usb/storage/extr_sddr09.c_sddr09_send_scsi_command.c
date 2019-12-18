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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int sddr09_send_command (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static int
sddr09_send_scsi_command(struct us_data *us,
			 unsigned char *command,
			 unsigned int command_len) {
	return sddr09_send_command(us, 0, USB_DIR_OUT, command, command_len);
}