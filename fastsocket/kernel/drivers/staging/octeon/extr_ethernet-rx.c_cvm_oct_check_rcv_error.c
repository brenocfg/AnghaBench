#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pre_chk; } ;
union cvmx_gmxx_rxx_frm_ctl {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  int uint8_t ;
struct TYPE_12__ {int err_code; } ;
struct TYPE_13__ {TYPE_4__ snoip; } ;
struct TYPE_10__ {int addr; } ;
struct TYPE_11__ {TYPE_2__ s; } ;
struct TYPE_14__ {int len; TYPE_5__ word2; int /*<<< orphan*/  ipprt; TYPE_3__ packet_ptr; } ;
typedef  TYPE_6__ cvmx_wqe_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_CTL (int,int) ; 
 int /*<<< orphan*/  DEBUGPRINT (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ USE_10MBPS_PREAMBLE_WORKAROUND ; 
 int /*<<< orphan*/  cvm_oct_free_work (TYPE_6__*) ; 
 int cvmx_helper_get_interface_index_num (int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_interface_num (int /*<<< orphan*/ ) ; 
 int* cvmx_phys_to_ptr (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvm_oct_check_rcv_error(cvmx_wqe_t *work)
{
	if ((work->word2.snoip.err_code == 10) && (work->len <= 64)) {
		/*
		 * Ignore length errors on min size packets. Some
		 * equipment incorrectly pads packets to 64+4FCS
		 * instead of 60+4FCS.  Note these packets still get
		 * counted as frame errors.
		 */
	} else
	    if (USE_10MBPS_PREAMBLE_WORKAROUND
		&& ((work->word2.snoip.err_code == 5)
		    || (work->word2.snoip.err_code == 7))) {

		/*
		 * We received a packet with either an alignment error
		 * or a FCS error. This may be signalling that we are
		 * running 10Mbps with GMXX_RXX_FRM_CTL[PRE_CHK}
		 * off. If this is the case we need to parse the
		 * packet to determine if we can remove a non spec
		 * preamble and generate a correct packet.
		 */
		int interface = cvmx_helper_get_interface_num(work->ipprt);
		int index = cvmx_helper_get_interface_index_num(work->ipprt);
		union cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;
		gmxx_rxx_frm_ctl.u64 =
		    cvmx_read_csr(CVMX_GMXX_RXX_FRM_CTL(index, interface));
		if (gmxx_rxx_frm_ctl.s.pre_chk == 0) {

			uint8_t *ptr =
			    cvmx_phys_to_ptr(work->packet_ptr.s.addr);
			int i = 0;

			while (i < work->len - 1) {
				if (*ptr != 0x55)
					break;
				ptr++;
				i++;
			}

			if (*ptr == 0xd5) {
				/*
				   DEBUGPRINT("Port %d received 0xd5 preamble\n", work->ipprt);
				 */
				work->packet_ptr.s.addr += i + 1;
				work->len -= i + 5;
			} else if ((*ptr & 0xf) == 0xd) {
				/*
				   DEBUGPRINT("Port %d received 0x?d preamble\n", work->ipprt);
				 */
				work->packet_ptr.s.addr += i;
				work->len -= i + 4;
				for (i = 0; i < work->len; i++) {
					*ptr =
					    ((*ptr & 0xf0) >> 4) |
					    ((*(ptr + 1) & 0xf) << 4);
					ptr++;
				}
			} else {
				DEBUGPRINT("Port %d unknown preamble, packet "
					   "dropped\n",
				     work->ipprt);
				/*
				   cvmx_helper_dump_packet(work);
				 */
				cvm_oct_free_work(work);
				return 1;
			}
		}
	} else {
		DEBUGPRINT("Port %d receive error code %d, packet dropped\n",
			   work->ipprt, work->word2.snoip.err_code);
		cvm_oct_free_work(work);
		return 1;
	}

	return 0;
}