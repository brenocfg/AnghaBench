#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_test {int flags; } ;
struct efx_self_tests {int dummy; } ;
struct efx_nic {scalar_t__ state; TYPE_1__* net_dev; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ETH_TEST_FL_FAILED ; 
 int ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_UP ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  dev_close (TYPE_1__*) ; 
 int dev_open (TYPE_1__*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ethtool_fill_self_tests (struct efx_nic*,struct efx_self_tests*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int efx_selftest (struct efx_nic*,struct efx_self_tests*,int) ; 
 int /*<<< orphan*/  kfree (struct efx_self_tests*) ; 
 struct efx_self_tests* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,TYPE_1__*,char*,char*,...) ; 

__attribute__((used)) static void efx_ethtool_self_test(struct net_device *net_dev,
				  struct ethtool_test *test, u64 *data)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_self_tests *efx_tests;
	int already_up;
	int rc = -ENOMEM;

	efx_tests = kzalloc(sizeof(*efx_tests), GFP_KERNEL);
	if (!efx_tests)
		goto fail;

	if (efx->state != STATE_READY) {
		rc = -EIO;
		goto fail1;
	}

	netif_info(efx, drv, efx->net_dev, "starting %sline testing\n",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

	/* We need rx buffers and interrupts. */
	already_up = (efx->net_dev->flags & IFF_UP);
	if (!already_up) {
		rc = dev_open(efx->net_dev);
		if (rc) {
			netif_err(efx, drv, efx->net_dev,
				  "failed opening device.\n");
			goto fail1;
		}
	}

	rc = efx_selftest(efx, efx_tests, test->flags);

	if (!already_up)
		dev_close(efx->net_dev);

	netif_info(efx, drv, efx->net_dev, "%s %sline self-tests\n",
		   rc == 0 ? "passed" : "failed",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

fail1:
	/* Fill ethtool results structures */
	efx_ethtool_fill_self_tests(efx, efx_tests, NULL, data);
	kfree(efx_tests);
fail:
	if (rc)
		test->flags |= ETH_TEST_FL_FAILED;
}