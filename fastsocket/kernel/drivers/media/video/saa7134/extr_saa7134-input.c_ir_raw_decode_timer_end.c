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
struct saa7134_dev {struct saa7134_card_ir* remote; } ;
struct saa7134_card_ir {int active; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_raw_decode_timer_end(unsigned long data)
{
	struct saa7134_dev *dev = (struct saa7134_dev *)data;
	struct saa7134_card_ir *ir = dev->remote;

	ir_raw_event_handle(dev->remote->dev);

	ir->active = false;
}