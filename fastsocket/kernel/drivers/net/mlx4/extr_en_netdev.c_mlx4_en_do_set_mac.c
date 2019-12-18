#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_priv {TYPE_1__* dev; int /*<<< orphan*/  prev_mac; int /*<<< orphan*/  base_qpn; scalar_t__ port_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx4_en_replace_mac (struct mlx4_en_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_do_set_mac(struct mlx4_en_priv *priv)
{
	int err = 0;

	if (priv->port_up) {
		/* Remove old MAC and insert the new one */
		err = mlx4_en_replace_mac(priv, priv->base_qpn,
					  priv->dev->dev_addr, priv->prev_mac);
		if (err)
			en_err(priv, "Failed changing HW MAC address\n");
		memcpy(priv->prev_mac, priv->dev->dev_addr,
		       sizeof(priv->prev_mac));
	} else
		en_dbg(HW, priv, "Port is down while registering mac, exiting...\n");

	return err;
}