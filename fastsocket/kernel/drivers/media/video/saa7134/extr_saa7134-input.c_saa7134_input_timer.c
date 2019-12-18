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
struct saa7134_card_ir {int /*<<< orphan*/  polling; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_key (struct saa7134_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saa7134_input_timer(unsigned long data)
{
	struct saa7134_dev *dev = (struct saa7134_dev *)data;
	struct saa7134_card_ir *ir = dev->remote;

	build_key(dev);
	mod_timer(&ir->timer, jiffies + msecs_to_jiffies(ir->polling));
}