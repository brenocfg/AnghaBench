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
typedef  int u16 ;
struct d11txh {int /*<<< orphan*/  TxFrameID; } ;
struct brcms_c_info {int /*<<< orphan*/  mc_fid_counter; } ;
struct brcms_bss_cfg {int dummy; } ;

/* Variables and functions */
 int TXFID_QUEUE_MASK ; 
 int TXFID_SEQ_MASK ; 
 int TXFID_SEQ_SHIFT ; 
 int TX_BCMC_FIFO ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16
bcmc_fid_generate(struct brcms_c_info *wlc, struct brcms_bss_cfg *bsscfg,
		  struct d11txh *txh)
{
	u16 frameid;

	frameid = le16_to_cpu(txh->TxFrameID) & ~(TXFID_SEQ_MASK |
						  TXFID_QUEUE_MASK);
	frameid |=
	    (((wlc->
	       mc_fid_counter++) << TXFID_SEQ_SHIFT) & TXFID_SEQ_MASK) |
	    TX_BCMC_FIFO;

	return frameid;
}