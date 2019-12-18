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
typedef  scalar_t__ u32 ;
struct emac_priv {TYPE_1__* ndev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_RXCP (scalar_t__) ; 
 int EMAC_TEARDOWN_VALUE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emac_rxch_teardown(struct emac_priv *priv, u32 ch)
{
	struct device *emac_dev = &priv->ndev->dev;
	u32 teardown_cnt = 0xFFFFFFF0; /* Some high value */

	while ((emac_read(EMAC_RXCP(ch)) & EMAC_TEARDOWN_VALUE) !=
	       EMAC_TEARDOWN_VALUE) {
		/* wait till tx teardown complete */
		cpu_relax(); /* TODO: check if this helps ... */
		--teardown_cnt;
		if (0 == teardown_cnt) {
			dev_err(emac_dev, "EMAC: RX teardown aborted\n");
			break;
		}
	}
	emac_write(EMAC_RXCP(ch), EMAC_TEARDOWN_VALUE);
}