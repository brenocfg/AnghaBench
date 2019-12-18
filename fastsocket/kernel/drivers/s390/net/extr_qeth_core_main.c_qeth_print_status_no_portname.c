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
struct TYPE_4__ {char* mcl_level; scalar_t__* portname; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__* gdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_get_cardname (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_get_cardname_short (struct qeth_card*) ; 

__attribute__((used)) static void qeth_print_status_no_portname(struct qeth_card *card)
{
	if (card->info.portname[0])
		dev_info(&card->gdev->dev, "Device is a%s "
		       "card%s%s%s\nwith link type %s "
		       "(no portname needed by interface).\n",
		       qeth_get_cardname(card),
		       (card->info.mcl_level[0]) ? " (level: " : "",
		       (card->info.mcl_level[0]) ? card->info.mcl_level : "",
		       (card->info.mcl_level[0]) ? ")" : "",
		       qeth_get_cardname_short(card));
	else
		dev_info(&card->gdev->dev, "Device is a%s "
		       "card%s%s%s\nwith link type %s.\n",
		       qeth_get_cardname(card),
		       (card->info.mcl_level[0]) ? " (level: " : "",
		       (card->info.mcl_level[0]) ? card->info.mcl_level : "",
		       (card->info.mcl_level[0]) ? ")" : "",
		       qeth_get_cardname_short(card));
}