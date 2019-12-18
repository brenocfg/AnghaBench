#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int port_bit; } ;
union cvmx_ipd_sub_port_fcs {void* u64; TYPE_3__ s; } ;
struct TYPE_8__ {scalar_t__ pcterr; } ;
union cvmx_gmxx_rxx_int_reg {void* u64; TYPE_1__ s; } ;
struct TYPE_9__ {int pre_chk; } ;
union cvmx_gmxx_rxx_frm_ctl {void* u64; TYPE_2__ s; } ;
struct octeon_ethernet {unsigned long long port; scalar_t__ link_info; int queue; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int speed; scalar_t__ full_duplex; scalar_t__ link_up; } ;
struct TYPE_12__ {scalar_t__ u64; TYPE_4__ s; } ;
typedef  TYPE_5__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_CTL (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_IPD_SUB_PORT_FCS ; 
 int /*<<< orphan*/  DEBUGPRINT (char*,int /*<<< orphan*/ ,...) ; 
 int INDEX (unsigned long long) ; 
 int INTERFACE (unsigned long long) ; 
 scalar_t__ USE_10MBPS_PREAMBLE_WORKAROUND ; 
 TYPE_5__ cvmx_helper_link_autoconf (unsigned long long) ; 
 TYPE_5__ cvmx_helper_link_get (unsigned long long) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  global_register_lock ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cvm_oct_rgmii_poll(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	unsigned long flags;
	cvmx_helper_link_info_t link_info;

	/*
	 * Take the global register lock since we are going to touch
	 * registers that affect more than one port.
	 */
	spin_lock_irqsave(&global_register_lock, flags);

	link_info = cvmx_helper_link_get(priv->port);
	if (link_info.u64 == priv->link_info) {

		/*
		 * If the 10Mbps preamble workaround is supported and we're
		 * at 10Mbps we may need to do some special checking.
		 */
		if (USE_10MBPS_PREAMBLE_WORKAROUND && (link_info.s.speed == 10)) {

			/*
			 * Read the GMXX_RXX_INT_REG[PCTERR] bit and
			 * see if we are getting preamble errors.
			 */
			int interface = INTERFACE(priv->port);
			int index = INDEX(priv->port);
			union cvmx_gmxx_rxx_int_reg gmxx_rxx_int_reg;
			gmxx_rxx_int_reg.u64 =
			    cvmx_read_csr(CVMX_GMXX_RXX_INT_REG
					  (index, interface));
			if (gmxx_rxx_int_reg.s.pcterr) {

				/*
				 * We are getting preamble errors at
				 * 10Mbps.  Most likely the PHY is
				 * giving us packets with mis aligned
				 * preambles. In order to get these
				 * packets we need to disable preamble
				 * checking and do it in software.
				 */
				union cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;
				union cvmx_ipd_sub_port_fcs ipd_sub_port_fcs;

				/* Disable preamble checking */
				gmxx_rxx_frm_ctl.u64 =
				    cvmx_read_csr(CVMX_GMXX_RXX_FRM_CTL
						  (index, interface));
				gmxx_rxx_frm_ctl.s.pre_chk = 0;
				cvmx_write_csr(CVMX_GMXX_RXX_FRM_CTL
					       (index, interface),
					       gmxx_rxx_frm_ctl.u64);

				/* Disable FCS stripping */
				ipd_sub_port_fcs.u64 =
				    cvmx_read_csr(CVMX_IPD_SUB_PORT_FCS);
				ipd_sub_port_fcs.s.port_bit &=
				    0xffffffffull ^ (1ull << priv->port);
				cvmx_write_csr(CVMX_IPD_SUB_PORT_FCS,
					       ipd_sub_port_fcs.u64);

				/* Clear any error bits */
				cvmx_write_csr(CVMX_GMXX_RXX_INT_REG
					       (index, interface),
					       gmxx_rxx_int_reg.u64);
				DEBUGPRINT("%s: Using 10Mbps with software "
					   "preamble removal\n",
				     dev->name);
			}
		}
		spin_unlock_irqrestore(&global_register_lock, flags);
		return;
	}

	/* If the 10Mbps preamble workaround is allowed we need to on
	   preamble checking, FCS stripping, and clear error bits on
	   every speed change. If errors occur during 10Mbps operation
	   the above code will change this stuff */
	if (USE_10MBPS_PREAMBLE_WORKAROUND) {

		union cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;
		union cvmx_ipd_sub_port_fcs ipd_sub_port_fcs;
		union cvmx_gmxx_rxx_int_reg gmxx_rxx_int_reg;
		int interface = INTERFACE(priv->port);
		int index = INDEX(priv->port);

		/* Enable preamble checking */
		gmxx_rxx_frm_ctl.u64 =
		    cvmx_read_csr(CVMX_GMXX_RXX_FRM_CTL(index, interface));
		gmxx_rxx_frm_ctl.s.pre_chk = 1;
		cvmx_write_csr(CVMX_GMXX_RXX_FRM_CTL(index, interface),
			       gmxx_rxx_frm_ctl.u64);
		/* Enable FCS stripping */
		ipd_sub_port_fcs.u64 = cvmx_read_csr(CVMX_IPD_SUB_PORT_FCS);
		ipd_sub_port_fcs.s.port_bit |= 1ull << priv->port;
		cvmx_write_csr(CVMX_IPD_SUB_PORT_FCS, ipd_sub_port_fcs.u64);
		/* Clear any error bits */
		gmxx_rxx_int_reg.u64 =
		    cvmx_read_csr(CVMX_GMXX_RXX_INT_REG(index, interface));
		cvmx_write_csr(CVMX_GMXX_RXX_INT_REG(index, interface),
			       gmxx_rxx_int_reg.u64);
	}

	link_info = cvmx_helper_link_autoconf(priv->port);
	priv->link_info = link_info.u64;
	spin_unlock_irqrestore(&global_register_lock, flags);

	/* Tell Linux */
	if (link_info.s.link_up) {

		if (!netif_carrier_ok(dev))
			netif_carrier_on(dev);
		if (priv->queue != -1)
			DEBUGPRINT
			    ("%s: %u Mbps %s duplex, port %2d, queue %2d\n",
			     dev->name, link_info.s.speed,
			     (link_info.s.full_duplex) ? "Full" : "Half",
			     priv->port, priv->queue);
		else
			DEBUGPRINT("%s: %u Mbps %s duplex, port %2d, POW\n",
				   dev->name, link_info.s.speed,
				   (link_info.s.full_duplex) ? "Full" : "Half",
				   priv->port);
	} else {

		if (netif_carrier_ok(dev))
			netif_carrier_off(dev);
		DEBUGPRINT("%s: Link down\n", dev->name);
	}
}