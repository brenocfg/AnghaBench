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
struct pwc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE_USER_DEFAULTS_FORMATTER ; 
 int /*<<< orphan*/  SET_STATUS_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pwc_save_user(struct pwc_device *pdev)
{
	return send_control_msg(pdev,
		SET_STATUS_CTL, SAVE_USER_DEFAULTS_FORMATTER, NULL, 0);
}