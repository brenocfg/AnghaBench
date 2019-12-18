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
struct ath_rx_status {int rs_datalen; int rs_rssi; int rs_rssi_ctl0; int rs_rssi_ctl1; int rs_rssi_ctl2; int rs_rssi_ext0; int rs_rssi_ext1; int rs_rssi_ext2; int rs_keyix; int rs_rate; int rs_more; int rs_isaggr; int rs_moreaggr; int rs_antenna; int evm4; unsigned int rs_phyerr; int /*<<< orphan*/  rs_status; int /*<<< orphan*/  rs_flags; int /*<<< orphan*/  evm3; int /*<<< orphan*/  evm2; int /*<<< orphan*/  evm1; int /*<<< orphan*/  evm0; int /*<<< orphan*/  rs_tstamp; } ;
struct ath_hw {int dummy; } ;
struct ar9003_rxs {int status11; int ds_info; int status2; int status5; int status1; int status4; int status10; int /*<<< orphan*/  status9; int /*<<< orphan*/  status8; int /*<<< orphan*/  status7; int /*<<< orphan*/  status6; int /*<<< orphan*/  status3; } ;

/* Variables and functions */
 int AR_2040 ; 
 int AR_CRCErr ; 
 int AR_CtrlStat ; 
 int AR_DataLen ; 
 int AR_DecryptBusyErr ; 
 int AR_DecryptCRCErr ; 
 int /*<<< orphan*/  AR_DescId ; 
 int AR_GI ; 
 int /*<<< orphan*/  AR_KeyIdx ; 
 int AR_KeyMiss ; 
 int AR_MichaelErr ; 
 int AR_PHYErr ; 
 int /*<<< orphan*/  AR_PHYErrCode ; 
 int AR_PostDelimCRCErr ; 
 int AR_PreDelimCRCErr ; 
 int AR_RxAggr ; 
 int /*<<< orphan*/  AR_RxAntenna ; 
 int AR_RxDone ; 
 int AR_RxFrameOK ; 
 int AR_RxKeyIdxValid ; 
 int AR_RxMore ; 
 int AR_RxMoreAggr ; 
 int /*<<< orphan*/  AR_RxRSSIAnt00 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt01 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt02 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt10 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt11 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt12 ; 
 int /*<<< orphan*/  AR_RxRSSICombined ; 
 int /*<<< orphan*/  AR_RxRate ; 
 int AR_TxRxDesc ; 
 unsigned int ATH9K_PHYERR_OFDM_RESTART ; 
 int /*<<< orphan*/  ATH9K_RXERR_CRC ; 
 int /*<<< orphan*/  ATH9K_RXERR_DECRYPT ; 
 int /*<<< orphan*/  ATH9K_RXERR_KEYMISS ; 
 int /*<<< orphan*/  ATH9K_RXERR_MIC ; 
 int /*<<< orphan*/  ATH9K_RXERR_PHY ; 
 int ATH9K_RXKEYIX_INVALID ; 
 int /*<<< orphan*/  ATH9K_RX_2040 ; 
 int /*<<< orphan*/  ATH9K_RX_DECRYPT_BUSY ; 
 int /*<<< orphan*/  ATH9K_RX_DELIM_CRC_POST ; 
 int /*<<< orphan*/  ATH9K_RX_DELIM_CRC_PRE ; 
 int /*<<< orphan*/  ATH9K_RX_GI ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int MS (int,int /*<<< orphan*/ ) ; 

int ath9k_hw_process_rxdesc_edma(struct ath_hw *ah, struct ath_rx_status *rxs,
				 void *buf_addr)
{
	struct ar9003_rxs *rxsp = (struct ar9003_rxs *) buf_addr;
	unsigned int phyerr;

	if ((rxsp->status11 & AR_RxDone) == 0)
		return -EINPROGRESS;

	if (MS(rxsp->ds_info, AR_DescId) != 0x168c)
		return -EINVAL;

	if ((rxsp->ds_info & (AR_TxRxDesc | AR_CtrlStat)) != 0)
		return -EINPROGRESS;

	rxs->rs_status = 0;
	rxs->rs_flags =  0;

	rxs->rs_datalen = rxsp->status2 & AR_DataLen;
	rxs->rs_tstamp =  rxsp->status3;

	/* XXX: Keycache */
	rxs->rs_rssi = MS(rxsp->status5, AR_RxRSSICombined);
	rxs->rs_rssi_ctl0 = MS(rxsp->status1, AR_RxRSSIAnt00);
	rxs->rs_rssi_ctl1 = MS(rxsp->status1, AR_RxRSSIAnt01);
	rxs->rs_rssi_ctl2 = MS(rxsp->status1, AR_RxRSSIAnt02);
	rxs->rs_rssi_ext0 = MS(rxsp->status5, AR_RxRSSIAnt10);
	rxs->rs_rssi_ext1 = MS(rxsp->status5, AR_RxRSSIAnt11);
	rxs->rs_rssi_ext2 = MS(rxsp->status5, AR_RxRSSIAnt12);

	if (rxsp->status11 & AR_RxKeyIdxValid)
		rxs->rs_keyix = MS(rxsp->status11, AR_KeyIdx);
	else
		rxs->rs_keyix = ATH9K_RXKEYIX_INVALID;

	rxs->rs_rate = MS(rxsp->status1, AR_RxRate);
	rxs->rs_more = (rxsp->status2 & AR_RxMore) ? 1 : 0;

	rxs->rs_isaggr = (rxsp->status11 & AR_RxAggr) ? 1 : 0;
	rxs->rs_moreaggr = (rxsp->status11 & AR_RxMoreAggr) ? 1 : 0;
	rxs->rs_antenna = (MS(rxsp->status4, AR_RxAntenna) & 0x7);
	rxs->rs_flags  = (rxsp->status4 & AR_GI) ? ATH9K_RX_GI : 0;
	rxs->rs_flags  |= (rxsp->status4 & AR_2040) ? ATH9K_RX_2040 : 0;

	rxs->evm0 = rxsp->status6;
	rxs->evm1 = rxsp->status7;
	rxs->evm2 = rxsp->status8;
	rxs->evm3 = rxsp->status9;
	rxs->evm4 = (rxsp->status10 & 0xffff);

	if (rxsp->status11 & AR_PreDelimCRCErr)
		rxs->rs_flags |= ATH9K_RX_DELIM_CRC_PRE;

	if (rxsp->status11 & AR_PostDelimCRCErr)
		rxs->rs_flags |= ATH9K_RX_DELIM_CRC_POST;

	if (rxsp->status11 & AR_DecryptBusyErr)
		rxs->rs_flags |= ATH9K_RX_DECRYPT_BUSY;

	if ((rxsp->status11 & AR_RxFrameOK) == 0) {
		/*
		 * AR_CRCErr will bet set to true if we're on the last
		 * subframe and the AR_PostDelimCRCErr is caught.
		 * In a way this also gives us a guarantee that when
		 * (!(AR_CRCErr) && (AR_PostDelimCRCErr)) we cannot
		 * possibly be reviewing the last subframe. AR_CRCErr
		 * is the CRC of the actual data.
		 */
		if (rxsp->status11 & AR_CRCErr)
			rxs->rs_status |= ATH9K_RXERR_CRC;
		else if (rxsp->status11 & AR_DecryptCRCErr)
			rxs->rs_status |= ATH9K_RXERR_DECRYPT;
		else if (rxsp->status11 & AR_MichaelErr)
			rxs->rs_status |= ATH9K_RXERR_MIC;
		if (rxsp->status11 & AR_PHYErr) {
			phyerr = MS(rxsp->status11, AR_PHYErrCode);
			/*
			 * If we reach a point here where AR_PostDelimCRCErr is
			 * true it implies we're *not* on the last subframe. In
			 * in that case that we know already that the CRC of
			 * the frame was OK, and MAC would send an ACK for that
			 * subframe, even if we did get a phy error of type
			 * ATH9K_PHYERR_OFDM_RESTART. This is only applicable
			 * to frame that are prior to the last subframe.
			 * The AR_PostDelimCRCErr is the CRC for the MPDU
			 * delimiter, which contains the 4 reserved bits,
			 * the MPDU length (12 bits), and follows the MPDU
			 * delimiter for an A-MPDU subframe (0x4E = 'N' ASCII).
			 */
			if ((phyerr == ATH9K_PHYERR_OFDM_RESTART) &&
			    (rxsp->status11 & AR_PostDelimCRCErr)) {
				rxs->rs_phyerr = 0;
			} else {
				rxs->rs_status |= ATH9K_RXERR_PHY;
				rxs->rs_phyerr = phyerr;
			}
		}
	}

	if (rxsp->status11 & AR_KeyMiss)
		rxs->rs_status |= ATH9K_RXERR_KEYMISS;

	return 0;
}