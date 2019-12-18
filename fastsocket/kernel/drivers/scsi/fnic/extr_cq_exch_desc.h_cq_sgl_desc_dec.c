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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct cq_sgl_desc {int tmpl; int sgl_err; int /*<<< orphan*/  tot_data_bytes; int /*<<< orphan*/  active_burst_offset; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int CQ_SGL_SGL_ERR_MASK ; 
 int CQ_SGL_TMPL_MASK ; 
 int /*<<< orphan*/  cq_desc_dec (struct cq_desc*,int*,int*,int*,int*) ; 

__attribute__((used)) static inline void cq_sgl_desc_dec(struct cq_sgl_desc *desc_ptr,
				   u8  *type,
				   u8  *color,
				   u16 *q_number,
				   u16 *exchange_id,
				   u32 *active_burst_offset,
				   u32 *tot_data_bytes,
				   u16 *tmpl,
				   u8  *sgl_err)
{
	/* Cheat a little by assuming exchange_id is the same as completed
	   index */
	cq_desc_dec((struct cq_desc *)desc_ptr, type, color, q_number,
		    exchange_id);
	*active_burst_offset = desc_ptr->active_burst_offset;
	*tot_data_bytes = desc_ptr->tot_data_bytes;
	*tmpl = desc_ptr->tmpl & CQ_SGL_TMPL_MASK;
	*sgl_err = desc_ptr->sgl_err & CQ_SGL_SGL_ERR_MASK;
}