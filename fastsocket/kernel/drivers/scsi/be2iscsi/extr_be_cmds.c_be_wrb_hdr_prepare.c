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
typedef  int u8 ;
struct be_mcc_wrb {int embedded; int payload_length; } ;

/* Variables and functions */
 int MCC_WRB_EMBEDDED_MASK ; 
 int MCC_WRB_SGE_CNT_MASK ; 
 int MCC_WRB_SGE_CNT_SHIFT ; 
 int /*<<< orphan*/  be_dws_cpu_to_le (struct be_mcc_wrb*,int) ; 

void be_wrb_hdr_prepare(struct be_mcc_wrb *wrb, int payload_len,
				bool embedded, u8 sge_cnt)
{
	if (embedded)
		wrb->embedded |= MCC_WRB_EMBEDDED_MASK;
	else
		wrb->embedded |= (sge_cnt & MCC_WRB_SGE_CNT_MASK) <<
						MCC_WRB_SGE_CNT_SHIFT;
	wrb->payload_length = payload_len;
	be_dws_cpu_to_le(wrb, 8);
}