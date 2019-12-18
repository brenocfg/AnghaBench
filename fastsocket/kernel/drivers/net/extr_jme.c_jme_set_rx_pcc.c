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
struct jme_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  JME_PCCRX0 ; 
 int PCCRXTO_MASK ; 
 int PCCRXTO_SHIFT ; 
 int PCCRX_MASK ; 
 int PCCRX_SHIFT ; 
#define  PCC_OFF 131 
 int PCC_OFF_CNT ; 
 int PCC_OFF_TO ; 
#define  PCC_P1 130 
 int PCC_P1_CNT ; 
 int PCC_P1_TO ; 
#define  PCC_P2 129 
 int PCC_P2_CNT ; 
 int PCC_P2_TO ; 
#define  PCC_P3 128 
 int PCC_P3_CNT ; 
 int PCC_P3_TO ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_rx_status (struct jme_adapter*,char*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
jme_set_rx_pcc(struct jme_adapter *jme, int p)
{
	switch (p) {
	case PCC_OFF:
		jwrite32(jme, JME_PCCRX0,
			((PCC_OFF_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_OFF_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P1:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P1_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P1_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P2:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P2_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P2_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	case PCC_P3:
		jwrite32(jme, JME_PCCRX0,
			((PCC_P3_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P3_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		break;
	default:
		break;
	}
	wmb();

	if (!(test_bit(JME_FLAG_POLL, &jme->flags)))
		msg_rx_status(jme, "Switched to PCC_P%d\n", p);
}