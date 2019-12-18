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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  PT_RESET_CONTROL_FORMATTER ; 
 int /*<<< orphan*/  SET_MPT_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int _pwc_mpt_reset(struct pwc_device *pdev, int flags)
{
	unsigned char buf;

	buf = flags & 0x03; // only lower two bits are currently used
	return send_control_msg(pdev,
		SET_MPT_CTL, PT_RESET_CONTROL_FORMATTER, &buf, sizeof(buf));
}