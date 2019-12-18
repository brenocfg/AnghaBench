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
typedef  int /*<<< orphan*/  u32 ;
struct tg3_napi {int /*<<< orphan*/  tx_desc_mapping; int /*<<< orphan*/  tx_ring; } ;
struct tg3 {int irq_max; struct tg3_napi* napi; } ;

/* Variables and functions */
 int BDINFO_FLAGS_MAXLEN_SHIFT ; 
 int /*<<< orphan*/  ENABLE_TSS ; 
 int /*<<< orphan*/  NIC_SRAM_SEND_RCB ; 
 int /*<<< orphan*/  NIC_SRAM_TX_BUFFER_DESC ; 
 scalar_t__ TG3_BDINFO_SIZE ; 
 int TG3_TX_RING_SIZE ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_set_bdinfo (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_tx_rcbs_init(struct tg3 *tp)
{
	int i = 0;
	u32 txrcb = NIC_SRAM_SEND_RCB;

	if (tg3_flag(tp, ENABLE_TSS))
		i++;

	for (; i < tp->irq_max; i++, txrcb += TG3_BDINFO_SIZE) {
		struct tg3_napi *tnapi = &tp->napi[i];

		if (!tnapi->tx_ring)
			continue;

		tg3_set_bdinfo(tp, txrcb, tnapi->tx_desc_mapping,
			       (TG3_TX_RING_SIZE << BDINFO_FLAGS_MAXLEN_SHIFT),
			       NIC_SRAM_TX_BUFFER_DESC);
	}
}