#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int stats_bitmap; int tx_ring_num; int rx_ring_num; TYPE_3__* mdev; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int MLX4_DEV_CAP_FLAG_UC_LOOPBACK ; 
 int MLX4_EN_NUM_SELF_TEST ; 
 int NUM_MAIN_STATS ; 
 int NUM_PKT_STATS ; 
 int NUM_PORT_STATS ; 
 int /*<<< orphan*/ * main_strings ; 
 int /*<<< orphan*/ * mlx4_en_test_names ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_get_strings(struct net_device *dev,
				uint32_t stringset, uint8_t *data)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int index = 0;
	int i;

	switch (stringset) {
	case ETH_SS_TEST:
		for (i = 0; i < MLX4_EN_NUM_SELF_TEST - 2; i++)
			strcpy(data + i * ETH_GSTRING_LEN, mlx4_en_test_names[i]);
		if (priv->mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UC_LOOPBACK)
			for (; i < MLX4_EN_NUM_SELF_TEST; i++)
				strcpy(data + i * ETH_GSTRING_LEN, mlx4_en_test_names[i]);
		break;

	case ETH_SS_STATS:
		/* Add main counters */
		if (!priv->stats_bitmap) {
			for (i = 0; i < NUM_MAIN_STATS; i++)
				strcpy(data + (index++) * ETH_GSTRING_LEN,
					main_strings[i]);
			for (i = 0; i < NUM_PORT_STATS; i++)
				strcpy(data + (index++) * ETH_GSTRING_LEN,
					main_strings[i +
					NUM_MAIN_STATS]);
			for (i = 0; i < NUM_PKT_STATS; i++)
				strcpy(data + (index++) * ETH_GSTRING_LEN,
					main_strings[i +
					NUM_MAIN_STATS +
					NUM_PORT_STATS]);
		} else
			for (i = 0; i < NUM_MAIN_STATS + NUM_PORT_STATS; i++) {
				if ((priv->stats_bitmap >> i) & 1) {
					strcpy(data +
					       (index++) * ETH_GSTRING_LEN,
					       main_strings[i]);
				}
				if (!(priv->stats_bitmap >> i))
					break;
			}
		for (i = 0; i < priv->tx_ring_num; i++) {
			sprintf(data + (index++) * ETH_GSTRING_LEN,
				"tx%d_packets", i);
			sprintf(data + (index++) * ETH_GSTRING_LEN,
				"tx%d_bytes", i);
		}
		for (i = 0; i < priv->rx_ring_num; i++) {
			sprintf(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_packets", i);
			sprintf(data + (index++) * ETH_GSTRING_LEN,
				"rx%d_bytes", i);
		}
		break;
	}
}