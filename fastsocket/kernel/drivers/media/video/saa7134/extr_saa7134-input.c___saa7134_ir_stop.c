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
struct saa7134_card_ir {int running; int active; int /*<<< orphan*/  timer; scalar_t__ raw_decode; scalar_t__ polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __saa7134_ir_stop(void *priv)
{
	struct saa7134_dev *dev = priv;
	struct saa7134_card_ir *ir;

	if (!dev || !dev->remote)
		return;

	ir  = dev->remote;
	if (!ir->running)
		return;

	if (ir->polling || ir->raw_decode)
		del_timer_sync(&ir->timer);

	ir->active = false;
	ir->running = false;

	return;
}