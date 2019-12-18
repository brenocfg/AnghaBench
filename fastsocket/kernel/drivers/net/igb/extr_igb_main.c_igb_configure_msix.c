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
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int eims_enable_mask; int eims_other; int num_q_vectors; int /*<<< orphan*/ * q_vector; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_EIAME ; 
 int E1000_CTRL_EXT_IRCA ; 
 int E1000_CTRL_EXT_PBA_CLR ; 
 int E1000_EIMS_OTHER ; 
 int /*<<< orphan*/  E1000_GPIE ; 
 int E1000_GPIE_EIAME ; 
 int E1000_GPIE_MSIX_MODE ; 
 int E1000_GPIE_NSICR ; 
 int E1000_GPIE_PBA ; 
 int /*<<< orphan*/  E1000_IVAR_MISC ; 
 int E1000_IVAR_VALID ; 
 int /*<<< orphan*/  E1000_MSIXBM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  igb_assign_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igb_configure_msix(struct igb_adapter *adapter)
{
	u32 tmp;
	int i, vector = 0;
	struct e1000_hw *hw = &adapter->hw;

	adapter->eims_enable_mask = 0;

	/* set vector for other causes, i.e. link changes */
	switch (hw->mac.type) {
	case e1000_82575:
		tmp = rd32(E1000_CTRL_EXT);
		/* enable MSI-X PBA support*/
		tmp |= E1000_CTRL_EXT_PBA_CLR;

		/* Auto-Mask interrupts upon ICR read. */
		tmp |= E1000_CTRL_EXT_EIAME;
		tmp |= E1000_CTRL_EXT_IRCA;

		wr32(E1000_CTRL_EXT, tmp);

		/* enable msix_other interrupt */
		array_wr32(E1000_MSIXBM(0), vector++, E1000_EIMS_OTHER);
		adapter->eims_other = E1000_EIMS_OTHER;

		break;

	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		/* Turn on MSI-X capability first, or our settings
		 * won't stick.  And it will take days to debug.
		 */
		wr32(E1000_GPIE, E1000_GPIE_MSIX_MODE |
		     E1000_GPIE_PBA | E1000_GPIE_EIAME |
		     E1000_GPIE_NSICR);

		/* enable msix_other interrupt */
		adapter->eims_other = 1 << vector;
		tmp = (vector++ | E1000_IVAR_VALID) << 8;

		wr32(E1000_IVAR_MISC, tmp);
		break;
	default:
		/* do nothing, since nothing else supports MSI-X */
		break;
	} /* switch (hw->mac.type) */

	adapter->eims_enable_mask |= adapter->eims_other;

	for (i = 0; i < adapter->num_q_vectors; i++)
		igb_assign_vector(adapter->q_vector[i], vector++);

	wrfl();
}