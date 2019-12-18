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
 int /*<<< orphan*/  AWB_CONTROL_SPEED_FORMATTER ; 
 int /*<<< orphan*/  SET_CHROM_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int pwc_set_wb_speed(struct pwc_device *pdev, int speed)
{
	unsigned char buf;

	/* useful range is 0x01..0x20 */
	buf = speed / 0x7f0;
	return send_control_msg(pdev,
		SET_CHROM_CTL, AWB_CONTROL_SPEED_FORMATTER, &buf, sizeof(buf));
}