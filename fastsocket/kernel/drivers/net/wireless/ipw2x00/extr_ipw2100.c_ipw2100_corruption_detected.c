#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ipw2100_status {int dummy; } ;
struct TYPE_5__ {struct ipw2100_status* drv; } ;
struct ipw2100_priv {TYPE_3__* net_dev; int /*<<< orphan*/  fatal_error; TYPE_1__ status_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_7__ {int name; TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW2100_ERR_C3_CORRUPTION ; 
 int IPW_AUX_HOST_RESET_REG_MASTER_DISABLED ; 
 int /*<<< orphan*/  IPW_AUX_HOST_RESET_REG_STOP_MASTER ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int,...) ; 
 int /*<<< orphan*/  IPW_REG_RESET_REG ; 
 int /*<<< orphan*/  IPW_WAIT_RESET_MASTER_ASSERT_COMPLETE_DELAY ; 
 int RX_QUEUE_LENGTH ; 
 int /*<<< orphan*/  SEARCH_SNAPSHOT ; 
 int SEARCH_SUCCESS ; 
 int ipw2100_match_buf (struct ipw2100_priv*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_buf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_register (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  schedule_reset (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw2100_corruption_detected(struct ipw2100_priv *priv, int i)
{
#ifdef IPW2100_DEBUG_C3
	struct ipw2100_status *status = &priv->status_queue.drv[i];
	u32 match, reg;
	int j;
#endif

	IPW_DEBUG_INFO(": PCI latency error detected at 0x%04zX.\n",
		       i * sizeof(struct ipw2100_status));

#ifdef IPW2100_DEBUG_C3
	/* Halt the firmware so we can get a good image */
	write_register(priv->net_dev, IPW_REG_RESET_REG,
		       IPW_AUX_HOST_RESET_REG_STOP_MASTER);
	j = 5;
	do {
		udelay(IPW_WAIT_RESET_MASTER_ASSERT_COMPLETE_DELAY);
		read_register(priv->net_dev, IPW_REG_RESET_REG, &reg);

		if (reg & IPW_AUX_HOST_RESET_REG_MASTER_DISABLED)
			break;
	} while (j--);

	match = ipw2100_match_buf(priv, (u8 *) status,
				  sizeof(struct ipw2100_status),
				  SEARCH_SNAPSHOT);
	if (match < SEARCH_SUCCESS)
		IPW_DEBUG_INFO("%s: DMA status match in Firmware at "
			       "offset 0x%06X, length %d:\n",
			       priv->net_dev->name, match,
			       sizeof(struct ipw2100_status));
	else
		IPW_DEBUG_INFO("%s: No DMA status match in "
			       "Firmware.\n", priv->net_dev->name);

	printk_buf((u8 *) priv->status_queue.drv,
		   sizeof(struct ipw2100_status) * RX_QUEUE_LENGTH);
#endif

	priv->fatal_error = IPW2100_ERR_C3_CORRUPTION;
	priv->net_dev->stats.rx_errors++;
	schedule_reset(priv);
}