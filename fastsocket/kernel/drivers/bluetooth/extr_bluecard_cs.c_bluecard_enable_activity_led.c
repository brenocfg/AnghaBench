#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  hw_state; TYPE_2__* p_dev; } ;
typedef  TYPE_3__ bluecard_info_t ;
struct TYPE_5__ {unsigned int BasePort1; } ;
struct TYPE_6__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_HAS_ACTIVITY_LED ; 
 int /*<<< orphan*/  CARD_HAS_PCCARD_ID ; 
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bluecard_enable_activity_led(bluecard_info_t *info)
{
	unsigned int iobase = info->p_dev->io.BasePort1;

	if (!test_bit(CARD_HAS_PCCARD_ID, &(info->hw_state)))
		return;

	if (test_bit(CARD_HAS_ACTIVITY_LED, &(info->hw_state))) {
		/* Enable activity LED */
		outb(0x10 | 0x40, iobase + 0x30);

		/* Stop the LED after HZ/4 */
		mod_timer(&(info->timer), jiffies + HZ / 4);
	} else {
		/* Enable power LED */
		outb(0x08 | 0x20, iobase + 0x30);

		/* Stop the LED after HZ/2 */
		mod_timer(&(info->timer), jiffies + HZ / 2);
	}
}