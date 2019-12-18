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
struct snd_usb_caiaqdev {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int,unsigned char const) ; 

__attribute__((used)) static inline void snd_caiaq_input_report_abs(struct snd_usb_caiaqdev *dev,
					      int axis, const unsigned char *buf,
					      int offset)
{
	input_report_abs(dev->input_dev, axis,
			 (buf[offset * 2] << 8) | buf[offset * 2 + 1]);
}