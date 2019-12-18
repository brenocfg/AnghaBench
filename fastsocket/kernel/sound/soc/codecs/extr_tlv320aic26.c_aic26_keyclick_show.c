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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aic26 {int /*<<< orphan*/  codec; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL2 ; 
 int aic26_reg_read_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct aic26* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t aic26_keyclick_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct aic26 *aic26 = dev_get_drvdata(dev);
	int val, amp, freq, len;

	val = aic26_reg_read_cache(&aic26->codec, AIC26_REG_AUDIO_CTRL2);
	amp = (val >> 12) & 0x7;
	freq = (125 << ((val >> 8) & 0x7)) >> 1;
	len = 2 * (1 + ((val >> 4) & 0xf));

	return sprintf(buf, "amp=%x freq=%iHz len=%iclks\n", amp, freq, len);
}