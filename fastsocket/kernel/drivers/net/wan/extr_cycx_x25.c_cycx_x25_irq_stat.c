#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cycx_x25_cmd {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats; } ;
struct TYPE_3__ {TYPE_2__ x; } ;
struct cycx_device {int /*<<< orphan*/  wait_stats; TYPE_1__ u; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  cycx_peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cycx_x25_dump_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hex_dump (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cycx_x25_irq_stat(struct cycx_device *card,
			      struct cycx_x25_cmd *cmd)
{
	cycx_peek(&card->hw, cmd->buf, &card->u.x.stats,
		  sizeof(card->u.x.stats));
	hex_dump("cycx_x25_irq_stat", (unsigned char*)&card->u.x.stats,
		 sizeof(card->u.x.stats));
	cycx_x25_dump_stats(&card->u.x.stats);
	wake_up_interruptible(&card->wait_stats);
}