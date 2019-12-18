#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {int dummy; } ;
struct if_sdio_packet {scalar_t__ model; struct if_sdio_packet* next; struct if_sdio_packet* packets; int /*<<< orphan*/  workqueue; TYPE_1__* priv; } ;
struct if_sdio_card {scalar_t__ model; struct if_sdio_card* next; struct if_sdio_card* packets; int /*<<< orphan*/  workqueue; TYPE_1__* priv; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int surpriseremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FUNC_SHUTDOWN ; 
 scalar_t__ IF_SDIO_MODEL_8688 ; 
 int /*<<< orphan*/  LBS_DEB_SDIO ; 
 scalar_t__ __lbs_cmd (TYPE_1__*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct if_sdio_packet*) ; 
 int /*<<< orphan*/  lbs_cmd_copyback ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*) ; 
 int /*<<< orphan*/  lbs_pr_alert (char*) ; 
 int /*<<< orphan*/  lbs_remove_card (TYPE_1__*) ; 
 int /*<<< orphan*/  lbs_stop_card (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct if_sdio_packet* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 scalar_t__ user_rmmod ; 

__attribute__((used)) static void if_sdio_remove(struct sdio_func *func)
{
	struct if_sdio_card *card;
	struct if_sdio_packet *packet;

	lbs_deb_enter(LBS_DEB_SDIO);

	card = sdio_get_drvdata(func);

	if (user_rmmod && (card->model == IF_SDIO_MODEL_8688)) {
		/*
		 * FUNC_SHUTDOWN is required for SD8688 WLAN/BT
		 * multiple functions
		 */
		struct cmd_header cmd;

		memset(&cmd, 0, sizeof(cmd));

		lbs_deb_sdio("send function SHUTDOWN command\n");
		if (__lbs_cmd(card->priv, CMD_FUNC_SHUTDOWN,
				&cmd, sizeof(cmd), lbs_cmd_copyback,
				(unsigned long) &cmd))
			lbs_pr_alert("CMD_FUNC_SHUTDOWN cmd failed\n");
	}


	lbs_deb_sdio("call remove card\n");
	lbs_stop_card(card->priv);
	lbs_remove_card(card->priv);
	card->priv->surpriseremoved = 1;

	flush_workqueue(card->workqueue);
	destroy_workqueue(card->workqueue);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	while (card->packets) {
		packet = card->packets;
		card->packets = card->packets->next;
		kfree(packet);
	}

	kfree(card);

	lbs_deb_leave(LBS_DEB_SDIO);
}