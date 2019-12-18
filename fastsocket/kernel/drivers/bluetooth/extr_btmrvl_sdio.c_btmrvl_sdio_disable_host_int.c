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
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIM_DISABLE ; 
 int btmrvl_sdio_disable_host_int_mask (struct btmrvl_sdio_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_disable_host_int(struct btmrvl_sdio_card *card)
{
	int ret;

	if (!card || !card->func)
		return -EINVAL;

	sdio_claim_host(card->func);

	ret = btmrvl_sdio_disable_host_int_mask(card, HIM_DISABLE);

	sdio_release_host(card->func);

	return ret;
}