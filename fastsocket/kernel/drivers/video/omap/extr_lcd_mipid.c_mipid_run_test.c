#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mipid_device {TYPE_1__* spi; int /*<<< orphan*/  fbdev; } ;
struct lcd_panel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int MIPID_TEST_FAILED ; 
 int MIPID_TEST_INVALID ; 
 int MIPID_TEST_RGB_LINES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int const,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  omapfb_write_first_pixel (int /*<<< orphan*/ ,int const) ; 
 int read_first_pixel (struct mipid_device*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct mipid_device* to_mipid_device (struct lcd_panel*) ; 

__attribute__((used)) static int mipid_run_test(struct lcd_panel *panel, int test_num)
{
	struct mipid_device *md = to_mipid_device(panel);
	static const u16 test_values[4] = {
		0x0000, 0xffff, 0xaaaa, 0x5555,
	};
	int i;

	if (test_num != MIPID_TEST_RGB_LINES)
		return MIPID_TEST_INVALID;

	for (i = 0; i < ARRAY_SIZE(test_values); i++) {
		int delay;
		unsigned long tmo;

		omapfb_write_first_pixel(md->fbdev, test_values[i]);
		tmo = jiffies + msecs_to_jiffies(100);
		delay = 25;
		while (1) {
			u16 pixel;

			msleep(delay);
			pixel = read_first_pixel(md);
			if (pixel == test_values[i])
				break;
			if (time_after(jiffies, tmo)) {
				dev_err(&md->spi->dev,
					"MIPI LCD RGB I/F test failed: "
					"expecting %04x, got %04x\n",
					test_values[i], pixel);
				return MIPID_TEST_FAILED;
			}
			delay = 10;
		}
	}

	return 0;
}