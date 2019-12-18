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
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  rx_unit; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_RX_UNIT_REG ; 
 int /*<<< orphan*/  sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_get_rx_unit(struct btmrvl_sdio_card *card)
{
	u8 reg;
	int ret;

	reg = sdio_readb(card->func, CARD_RX_UNIT_REG, &ret);
	if (!ret)
		card->rx_unit = reg;

	return ret;
}