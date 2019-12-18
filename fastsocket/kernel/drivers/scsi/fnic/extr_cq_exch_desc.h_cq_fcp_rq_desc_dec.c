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
typedef  int u32 ;
typedef  int u16 ;
struct cq_fcp_rq_desc {int completed_index_eop_sop_prt; int exchange_id; int tmpl; int bytes_written; int vlan; int sof; int fcs_fer_fck; int eof; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int CQ_FCP_RQ_DESC_BYTES_WRITTEN_MASK ; 
 int CQ_FCP_RQ_DESC_FCOE_ERR_MASK ; 
 int CQ_FCP_RQ_DESC_FCOE_ERR_SHIFT ; 
 int CQ_FCP_RQ_DESC_FCS_OK_MASK ; 
 int CQ_FCP_RQ_DESC_FCS_OK_SHIFT ; 
 int CQ_FCP_RQ_DESC_FC_CRC_OK_MASK ; 
 int CQ_FCP_RQ_DESC_FLAGS_EOP ; 
 int CQ_FCP_RQ_DESC_FLAGS_PRT ; 
 int CQ_FCP_RQ_DESC_FLAGS_SOP ; 
 int CQ_FCP_RQ_DESC_PACKET_ERR_MASK ; 
 int CQ_FCP_RQ_DESC_PACKET_ERR_SHIFT ; 
 int CQ_FCP_RQ_DESC_TMPL_MASK ; 
 int CQ_FCP_RQ_DESC_VS_STRIPPED_MASK ; 
 int CQ_FCP_RQ_DESC_VS_STRIPPED_SHIFT ; 
 int /*<<< orphan*/  cq_desc_dec (struct cq_desc*,int*,int*,int*,int*) ; 

__attribute__((used)) static inline void cq_fcp_rq_desc_dec(struct cq_fcp_rq_desc *desc_ptr,
				      u8  *type,
				      u8  *color,
				      u16 *q_number,
				      u16 *completed_index,
				      u8  *eop,
				      u8  *sop,
				      u8  *fck,
				      u16 *exchange_id,
				      u16 *tmpl,
				      u32 *bytes_written,
				      u8  *sof,
				      u8  *eof,
				      u8  *ingress_port,
				      u8  *packet_err,
				      u8  *fcoe_err,
				      u8  *fcs_ok,
				      u8  *vlan_stripped,
				      u16 *vlan)
{
	cq_desc_dec((struct cq_desc *)desc_ptr, type,
		    color, q_number, completed_index);
	*eop = (desc_ptr->completed_index_eop_sop_prt &
		CQ_FCP_RQ_DESC_FLAGS_EOP) ? 1 : 0;
	*sop = (desc_ptr->completed_index_eop_sop_prt &
		CQ_FCP_RQ_DESC_FLAGS_SOP) ? 1 : 0;
	*ingress_port =
		(desc_ptr->completed_index_eop_sop_prt &
		 CQ_FCP_RQ_DESC_FLAGS_PRT) ? 1 : 0;
	*exchange_id = desc_ptr->exchange_id;
	*tmpl = desc_ptr->tmpl & CQ_FCP_RQ_DESC_TMPL_MASK;
	*bytes_written =
		desc_ptr->bytes_written & CQ_FCP_RQ_DESC_BYTES_WRITTEN_MASK;
	*packet_err =
		(desc_ptr->bytes_written & CQ_FCP_RQ_DESC_PACKET_ERR_MASK) >>
		CQ_FCP_RQ_DESC_PACKET_ERR_SHIFT;
	*vlan_stripped =
		(desc_ptr->bytes_written & CQ_FCP_RQ_DESC_VS_STRIPPED_MASK) >>
		CQ_FCP_RQ_DESC_VS_STRIPPED_SHIFT;
	*vlan = desc_ptr->vlan;
	*sof = desc_ptr->sof;
	*fck = desc_ptr->fcs_fer_fck & CQ_FCP_RQ_DESC_FC_CRC_OK_MASK;
	*fcoe_err = (desc_ptr->fcs_fer_fck & CQ_FCP_RQ_DESC_FCOE_ERR_MASK) >>
		CQ_FCP_RQ_DESC_FCOE_ERR_SHIFT;
	*eof = desc_ptr->eof;
	*fcs_ok =
		(desc_ptr->fcs_fer_fck & CQ_FCP_RQ_DESC_FCS_OK_MASK) >>
		CQ_FCP_RQ_DESC_FCS_OK_SHIFT;
}