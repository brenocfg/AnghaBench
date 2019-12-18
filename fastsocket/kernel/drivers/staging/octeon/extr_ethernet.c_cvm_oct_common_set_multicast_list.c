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
struct TYPE_2__ {int bcst; int mcst; int cam_mode; } ;
union cvmx_gmxx_rxx_adr_ctl {int u64; TYPE_1__ s; } ;
union cvmx_gmxx_prtx_cfg {unsigned long long u64; } ;
struct octeon_ethernet {int /*<<< orphan*/  port; } ;
struct net_device {int flags; scalar_t__ mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM_EN (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CTL (int,int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cvm_oct_common_set_multicast_list(struct net_device *dev)
{
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);

	if ((interface < 2)
	    && (cvmx_helper_interface_get_mode(interface) !=
		CVMX_HELPER_INTERFACE_MODE_SPI)) {
		union cvmx_gmxx_rxx_adr_ctl control;
		control.u64 = 0;
		control.s.bcst = 1;	/* Allow broadcast MAC addresses */

		if (dev->mc_list || (dev->flags & IFF_ALLMULTI) ||
		    (dev->flags & IFF_PROMISC))
			/* Force accept multicast packets */
			control.s.mcst = 2;
		else
			/* Force reject multicat packets */
			control.s.mcst = 1;

		if (dev->flags & IFF_PROMISC)
			/*
			 * Reject matches if promisc. Since CAM is
			 * shut off, should accept everything.
			 */
			control.s.cam_mode = 0;
		else
			/* Filter packets based on the CAM */
			control.s.cam_mode = 1;

		gmx_cfg.u64 =
		    cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface),
			       gmx_cfg.u64 & ~1ull);

		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CTL(index, interface),
			       control.u64);
		if (dev->flags & IFF_PROMISC)
			cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM_EN
				       (index, interface), 0);
		else
			cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM_EN
				       (index, interface), 1);

		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface),
			       gmx_cfg.u64);
	}
}