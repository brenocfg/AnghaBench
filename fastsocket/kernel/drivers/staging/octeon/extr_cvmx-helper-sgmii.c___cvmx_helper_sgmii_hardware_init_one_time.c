#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int link; int dup; int speed; } ;
union cvmx_pcsx_sgmx_an_adv_reg {void* u64; TYPE_5__ s; } ;
struct TYPE_10__ {scalar_t__ mac_phy; scalar_t__ mode; } ;
union cvmx_pcsx_miscx_ctl_reg {TYPE_4__ s; void* u64; } ;
struct TYPE_8__ {unsigned long long count; } ;
union cvmx_pcsx_linkx_timer_count_reg {void* u64; TYPE_2__ s; } ;
struct TYPE_9__ {int pause; int hfd; int fd; scalar_t__ rem_flt; } ;
union cvmx_pcsx_anx_adv_reg {void* u64; TYPE_3__ s; } ;
struct TYPE_7__ {scalar_t__ en; } ;
union cvmx_gmxx_prtx_cfg {void* u64; TYPE_1__ s; } ;
typedef  unsigned long long uint64_t ;
struct TYPE_12__ {int cpu_clock_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_ANX_ADV_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_LINKX_TIMER_COUNT_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_MISCX_CTL_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_SGMX_AN_ADV_REG (int,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_6__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int __cvmx_helper_sgmii_hardware_init_one_time(int interface, int index)
{
	const uint64_t clock_mhz = cvmx_sysinfo_get()->cpu_clock_hz / 1000000;
	union cvmx_pcsx_miscx_ctl_reg pcs_misc_ctl_reg;
	union cvmx_pcsx_linkx_timer_count_reg pcsx_linkx_timer_count_reg;
	union cvmx_gmxx_prtx_cfg gmxx_prtx_cfg;

	/* Disable GMX */
	gmxx_prtx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	gmxx_prtx_cfg.s.en = 0;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmxx_prtx_cfg.u64);

	/*
	 * Write PCS*_LINK*_TIMER_COUNT_REG[COUNT] with the
	 * appropriate value. 1000BASE-X specifies a 10ms
	 * interval. SGMII specifies a 1.6ms interval.
	 */
	pcs_misc_ctl_reg.u64 =
	    cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface));
	pcsx_linkx_timer_count_reg.u64 =
	    cvmx_read_csr(CVMX_PCSX_LINKX_TIMER_COUNT_REG(index, interface));
	if (pcs_misc_ctl_reg.s.mode) {
		/* 1000BASE-X */
		pcsx_linkx_timer_count_reg.s.count =
		    (10000ull * clock_mhz) >> 10;
	} else {
		/* SGMII */
		pcsx_linkx_timer_count_reg.s.count =
		    (1600ull * clock_mhz) >> 10;
	}
	cvmx_write_csr(CVMX_PCSX_LINKX_TIMER_COUNT_REG(index, interface),
		       pcsx_linkx_timer_count_reg.u64);

	/*
	 * Write the advertisement register to be used as the
	 * tx_Config_Reg<D15:D0> of the autonegotiation.  In
	 * 1000BASE-X mode, tx_Config_Reg<D15:D0> is PCS*_AN*_ADV_REG.
	 * In SGMII PHY mode, tx_Config_Reg<D15:D0> is
	 * PCS*_SGM*_AN_ADV_REG.  In SGMII MAC mode,
	 * tx_Config_Reg<D15:D0> is the fixed value 0x4001, so this
	 * step can be skipped.
	 */
	if (pcs_misc_ctl_reg.s.mode) {
		/* 1000BASE-X */
		union cvmx_pcsx_anx_adv_reg pcsx_anx_adv_reg;
		pcsx_anx_adv_reg.u64 =
		    cvmx_read_csr(CVMX_PCSX_ANX_ADV_REG(index, interface));
		pcsx_anx_adv_reg.s.rem_flt = 0;
		pcsx_anx_adv_reg.s.pause = 3;
		pcsx_anx_adv_reg.s.hfd = 1;
		pcsx_anx_adv_reg.s.fd = 1;
		cvmx_write_csr(CVMX_PCSX_ANX_ADV_REG(index, interface),
			       pcsx_anx_adv_reg.u64);
	} else {
		union cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;
		pcsx_miscx_ctl_reg.u64 =
		    cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface));
		if (pcsx_miscx_ctl_reg.s.mac_phy) {
			/* PHY Mode */
			union cvmx_pcsx_sgmx_an_adv_reg pcsx_sgmx_an_adv_reg;
			pcsx_sgmx_an_adv_reg.u64 =
			    cvmx_read_csr(CVMX_PCSX_SGMX_AN_ADV_REG
					  (index, interface));
			pcsx_sgmx_an_adv_reg.s.link = 1;
			pcsx_sgmx_an_adv_reg.s.dup = 1;
			pcsx_sgmx_an_adv_reg.s.speed = 2;
			cvmx_write_csr(CVMX_PCSX_SGMX_AN_ADV_REG
				       (index, interface),
				       pcsx_sgmx_an_adv_reg.u64);
		} else {
			/* MAC Mode - Nothing to do */
		}
	}
	return 0;
}