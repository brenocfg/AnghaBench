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
struct saa7134_dev {scalar_t__ empress_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_SPECIAL_MODE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ts_reset_encoder(struct saa7134_dev* dev)
{
	if (!dev->empress_started)
		return;

	saa_writeb(SAA7134_SPECIAL_MODE, 0x00);
	msleep(10);
	saa_writeb(SAA7134_SPECIAL_MODE, 0x01);
	msleep(100);
	dev->empress_started = 0;
}