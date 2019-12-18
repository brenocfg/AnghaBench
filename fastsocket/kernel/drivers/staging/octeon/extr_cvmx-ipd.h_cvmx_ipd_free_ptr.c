#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int rst; } ;
union cvmx_pip_sft_rst {void* u64; TYPE_8__ s; } ;
struct TYPE_9__ {scalar_t__ ptr; } ;
union cvmx_ipd_wqe_ptr_valid {TYPE_1__ s; void* u64; } ;
struct TYPE_14__ {int cena; int raddr; int max_cnts; int wraddr; int praddr; scalar_t__ ptr; } ;
union cvmx_ipd_pwp_ptr_fifo_ctl {void* u64; TYPE_6__ s; } ;
struct TYPE_13__ {int wqe_pcnt; int pfif_cnt; int pkt_pcnt; scalar_t__ pktv_cnt; scalar_t__ wqev_cnt; } ;
union cvmx_ipd_ptr_count {TYPE_5__ s; void* u64; } ;
struct TYPE_11__ {int max_pkt; int cena; int raddr; scalar_t__ ptr; } ;
union cvmx_ipd_prc_port_ptr_fifo_ctl {void* u64; TYPE_3__ s; } ;
struct TYPE_12__ {int cena; int raddr; int praddr; int max_pkt; scalar_t__ ptr; } ;
union cvmx_ipd_prc_hold_ptr_fifo_ctl {void* u64; TYPE_4__ s; } ;
struct TYPE_10__ {int ptr; } ;
union cvmx_ipd_pkt_ptr_valid {TYPE_2__ s; void* u64; } ;
struct TYPE_15__ {int reset; scalar_t__ no_wptr; } ;
union cvmx_ipd_ctl_status {void* u64; TYPE_7__ s; } ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_IPD_CTL_STATUS ; 
 int /*<<< orphan*/  CVMX_IPD_PKT_PTR_VALID ; 
 int /*<<< orphan*/  CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL ; 
 int /*<<< orphan*/  CVMX_IPD_PRC_PORT_PTR_FIFO_CTL ; 
 int /*<<< orphan*/  CVMX_IPD_PTR_COUNT ; 
 int /*<<< orphan*/  CVMX_IPD_PWP_PTR_FIFO_CTL ; 
 int /*<<< orphan*/  CVMX_IPD_WQE_PTR_VALID ; 
 int /*<<< orphan*/  CVMX_PIP_SFT_RST ; 
 int /*<<< orphan*/  OCTEON_CN38XX_PASS1 ; 
 int /*<<< orphan*/  OCTEON_CN38XX_PASS2 ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NO_WPTR ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_fpa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_phys_to_ptr (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_ipd_free_ptr(void)
{
	/* Only CN38XXp{1,2} cannot read pointer out of the IPD */
	if (!OCTEON_IS_MODEL(OCTEON_CN38XX_PASS1)
	    && !OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2)) {
		int no_wptr = 0;
		union cvmx_ipd_ptr_count ipd_ptr_count;
		ipd_ptr_count.u64 = cvmx_read_csr(CVMX_IPD_PTR_COUNT);

		/* Handle Work Queue Entry in cn56xx and cn52xx */
		if (octeon_has_feature(OCTEON_FEATURE_NO_WPTR)) {
			union cvmx_ipd_ctl_status ipd_ctl_status;
			ipd_ctl_status.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);
			if (ipd_ctl_status.s.no_wptr)
				no_wptr = 1;
		}

		/* Free the prefetched WQE */
		if (ipd_ptr_count.s.wqev_cnt) {
			union cvmx_ipd_wqe_ptr_valid ipd_wqe_ptr_valid;
			ipd_wqe_ptr_valid.u64 =
			    cvmx_read_csr(CVMX_IPD_WQE_PTR_VALID);
			if (no_wptr)
				cvmx_fpa_free(cvmx_phys_to_ptr
					      ((uint64_t) ipd_wqe_ptr_valid.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			else
				cvmx_fpa_free(cvmx_phys_to_ptr
					      ((uint64_t) ipd_wqe_ptr_valid.s.
					       ptr << 7), CVMX_FPA_WQE_POOL, 0);
		}

		/* Free all WQE in the fifo */
		if (ipd_ptr_count.s.wqe_pcnt) {
			int i;
			union cvmx_ipd_pwp_ptr_fifo_ctl ipd_pwp_ptr_fifo_ctl;
			ipd_pwp_ptr_fifo_ctl.u64 =
			    cvmx_read_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
			for (i = 0; i < ipd_ptr_count.s.wqe_pcnt; i++) {
				ipd_pwp_ptr_fifo_ctl.s.cena = 0;
				ipd_pwp_ptr_fifo_ctl.s.raddr =
				    ipd_pwp_ptr_fifo_ctl.s.max_cnts +
				    (ipd_pwp_ptr_fifo_ctl.s.wraddr +
				     i) % ipd_pwp_ptr_fifo_ctl.s.max_cnts;
				cvmx_write_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
					       ipd_pwp_ptr_fifo_ctl.u64);
				ipd_pwp_ptr_fifo_ctl.u64 =
				    cvmx_read_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
				if (no_wptr)
					cvmx_fpa_free(cvmx_phys_to_ptr
						      ((uint64_t)
						       ipd_pwp_ptr_fifo_ctl.s.
						       ptr << 7),
						      CVMX_FPA_PACKET_POOL, 0);
				else
					cvmx_fpa_free(cvmx_phys_to_ptr
						      ((uint64_t)
						       ipd_pwp_ptr_fifo_ctl.s.
						       ptr << 7),
						      CVMX_FPA_WQE_POOL, 0);
			}
			ipd_pwp_ptr_fifo_ctl.s.cena = 1;
			cvmx_write_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
				       ipd_pwp_ptr_fifo_ctl.u64);
		}

		/* Free the prefetched packet */
		if (ipd_ptr_count.s.pktv_cnt) {
			union cvmx_ipd_pkt_ptr_valid ipd_pkt_ptr_valid;
			ipd_pkt_ptr_valid.u64 =
			    cvmx_read_csr(CVMX_IPD_PKT_PTR_VALID);
			cvmx_fpa_free(cvmx_phys_to_ptr
				      (ipd_pkt_ptr_valid.s.ptr << 7),
				      CVMX_FPA_PACKET_POOL, 0);
		}

		/* Free the per port prefetched packets */
		if (1) {
			int i;
			union cvmx_ipd_prc_port_ptr_fifo_ctl
			    ipd_prc_port_ptr_fifo_ctl;
			ipd_prc_port_ptr_fifo_ctl.u64 =
			    cvmx_read_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL);

			for (i = 0; i < ipd_prc_port_ptr_fifo_ctl.s.max_pkt;
			     i++) {
				ipd_prc_port_ptr_fifo_ctl.s.cena = 0;
				ipd_prc_port_ptr_fifo_ctl.s.raddr =
				    i % ipd_prc_port_ptr_fifo_ctl.s.max_pkt;
				cvmx_write_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL,
					       ipd_prc_port_ptr_fifo_ctl.u64);
				ipd_prc_port_ptr_fifo_ctl.u64 =
				    cvmx_read_csr
				    (CVMX_IPD_PRC_PORT_PTR_FIFO_CTL);
				cvmx_fpa_free(cvmx_phys_to_ptr
					      ((uint64_t)
					       ipd_prc_port_ptr_fifo_ctl.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			}
			ipd_prc_port_ptr_fifo_ctl.s.cena = 1;
			cvmx_write_csr(CVMX_IPD_PRC_PORT_PTR_FIFO_CTL,
				       ipd_prc_port_ptr_fifo_ctl.u64);
		}

		/* Free all packets in the holding fifo */
		if (ipd_ptr_count.s.pfif_cnt) {
			int i;
			union cvmx_ipd_prc_hold_ptr_fifo_ctl
			    ipd_prc_hold_ptr_fifo_ctl;

			ipd_prc_hold_ptr_fifo_ctl.u64 =
			    cvmx_read_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL);

			for (i = 0; i < ipd_ptr_count.s.pfif_cnt; i++) {
				ipd_prc_hold_ptr_fifo_ctl.s.cena = 0;
				ipd_prc_hold_ptr_fifo_ctl.s.raddr =
				    (ipd_prc_hold_ptr_fifo_ctl.s.praddr +
				     i) % ipd_prc_hold_ptr_fifo_ctl.s.max_pkt;
				cvmx_write_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL,
					       ipd_prc_hold_ptr_fifo_ctl.u64);
				ipd_prc_hold_ptr_fifo_ctl.u64 =
				    cvmx_read_csr
				    (CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL);
				cvmx_fpa_free(cvmx_phys_to_ptr
					      ((uint64_t)
					       ipd_prc_hold_ptr_fifo_ctl.s.
					       ptr << 7), CVMX_FPA_PACKET_POOL,
					      0);
			}
			ipd_prc_hold_ptr_fifo_ctl.s.cena = 1;
			cvmx_write_csr(CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL,
				       ipd_prc_hold_ptr_fifo_ctl.u64);
		}

		/* Free all packets in the fifo */
		if (ipd_ptr_count.s.pkt_pcnt) {
			int i;
			union cvmx_ipd_pwp_ptr_fifo_ctl ipd_pwp_ptr_fifo_ctl;
			ipd_pwp_ptr_fifo_ctl.u64 =
			    cvmx_read_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);

			for (i = 0; i < ipd_ptr_count.s.pkt_pcnt; i++) {
				ipd_pwp_ptr_fifo_ctl.s.cena = 0;
				ipd_pwp_ptr_fifo_ctl.s.raddr =
				    (ipd_pwp_ptr_fifo_ctl.s.praddr +
				     i) % ipd_pwp_ptr_fifo_ctl.s.max_cnts;
				cvmx_write_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
					       ipd_pwp_ptr_fifo_ctl.u64);
				ipd_pwp_ptr_fifo_ctl.u64 =
				    cvmx_read_csr(CVMX_IPD_PWP_PTR_FIFO_CTL);
				cvmx_fpa_free(cvmx_phys_to_ptr
					      ((uint64_t) ipd_pwp_ptr_fifo_ctl.
					       s.ptr << 7),
					      CVMX_FPA_PACKET_POOL, 0);
			}
			ipd_pwp_ptr_fifo_ctl.s.cena = 1;
			cvmx_write_csr(CVMX_IPD_PWP_PTR_FIFO_CTL,
				       ipd_pwp_ptr_fifo_ctl.u64);
		}

		/* Reset the IPD to get all buffers out of it */
		{
			union cvmx_ipd_ctl_status ipd_ctl_status;
			ipd_ctl_status.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);
			ipd_ctl_status.s.reset = 1;
			cvmx_write_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_status.u64);
		}

		/* Reset the PIP */
		{
			union cvmx_pip_sft_rst pip_sft_rst;
			pip_sft_rst.u64 = cvmx_read_csr(CVMX_PIP_SFT_RST);
			pip_sft_rst.s.rst = 1;
			cvmx_write_csr(CVMX_PIP_SFT_RST, pip_sft_rst.u64);
		}
	}
}