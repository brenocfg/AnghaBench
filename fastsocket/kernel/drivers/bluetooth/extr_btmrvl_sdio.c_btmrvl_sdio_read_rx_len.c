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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct btmrvl_sdio_card {int rx_unit; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_RX_LEN_REG ; 
 scalar_t__ sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_read_rx_len(struct btmrvl_sdio_card *card, u16 *dat)
{
	u8 reg;
	int ret;

	reg = sdio_readb(card->func, CARD_RX_LEN_REG, &ret);
	if (!ret)
		*dat = (u16) reg << card->rx_unit;

	return ret;
}