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
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  HOST_INT_MASK_REG ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_enable_host_int_mask(struct btmrvl_sdio_card *card,
								u8 mask)
{
	int ret;

	sdio_writeb(card->func, mask, HOST_INT_MASK_REG, &ret);
	if (ret) {
		BT_ERR("Unable to enable the host interrupt!");
		ret = -EIO;
	}

	return ret;
}