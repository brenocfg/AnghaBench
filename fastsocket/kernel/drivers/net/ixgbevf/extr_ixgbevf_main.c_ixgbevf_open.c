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
struct net_device {int dummy; } ;
struct ixgbe_hw {scalar_t__ adapter_stopped; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  num_msix_vectors; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VTEICR ; 
 int /*<<< orphan*/  __IXGBEVF_TESTING ; 
 int /*<<< orphan*/  ixgbevf_configure (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_down (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_free_all_rx_resources (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_free_all_tx_resources (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_irq_enable (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_map_rings_to_vectors (struct ixgbevf_adapter*) ; 
 int ixgbevf_request_irq (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int ixgbevf_setup_all_rx_resources (struct ixgbevf_adapter*) ; 
 int ixgbevf_setup_all_tx_resources (struct ixgbevf_adapter*) ; 
 int ixgbevf_setup_queues (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_up_complete (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbevf_open(struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	int err;

	/* A previous failure to open the device because of a lack of
	 * available MSIX vector resources may have reset the number
	 * of msix vectors variable to zero.  The only way to recover
	 * is to unload/reload the driver and hope that the system has
	 * been able to recover some MSIX vector resources.
	 */
	if (!adapter->num_msix_vectors)
		return -ENOMEM;

	/* disallow open during test */
	if (test_bit(__IXGBEVF_TESTING, &adapter->state))
		return -EBUSY;

	if (hw->adapter_stopped) {
		ixgbevf_reset(adapter);
		/* if adapter is still stopped then PF isn't up and
		 * the vf can't start. */
		if (hw->adapter_stopped) {
			err = IXGBE_ERR_MBX;
			pr_err("Unable to start - perhaps the PF Driver isn't "
			       "up yet\n");
			goto err_setup_reset;
		}
	}

	/* setup queue reg_idx and Rx queue count */
	err = ixgbevf_setup_queues(adapter);
	if (err)
		goto err_setup_queues;

	/* allocate transmit descriptors */
	err = ixgbevf_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = ixgbevf_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	ixgbevf_configure(adapter);

	/*
	 * Map the Tx/Rx rings to the vectors we were allotted.
	 * if request_irq will be called in this function map_rings
	 * must be called *before* up_complete
	 */
	ixgbevf_map_rings_to_vectors(adapter);

	ixgbevf_up_complete(adapter);

	/* clear any pending interrupts, may auto mask */
	IXGBE_READ_REG(hw, IXGBE_VTEICR);
	err = ixgbevf_request_irq(adapter);
	if (err)
		goto err_req_irq;

	ixgbevf_irq_enable(adapter);

	return 0;

err_req_irq:
	ixgbevf_down(adapter);
err_setup_rx:
	ixgbevf_free_all_rx_resources(adapter);
err_setup_tx:
	ixgbevf_free_all_tx_resources(adapter);
err_setup_queues:
	ixgbevf_reset(adapter);

err_setup_reset:

	return err;
}