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
struct mwl8k_priv {int /*<<< orphan*/  fw_helper; int /*<<< orphan*/  fw_ucode; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl8k_release_fw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_release_firmware(struct mwl8k_priv *priv)
{
	mwl8k_release_fw(&priv->fw_ucode);
	mwl8k_release_fw(&priv->fw_helper);
}