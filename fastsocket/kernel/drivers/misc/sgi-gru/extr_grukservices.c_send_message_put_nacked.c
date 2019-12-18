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
struct gru_message_queue_desc {int mq_gpa; int /*<<< orphan*/  interrupt_vector; int /*<<< orphan*/  interrupt_apicid; int /*<<< orphan*/  interrupt_pnode; } ;

/* Variables and functions */
 int CBS_IDLE ; 
 int /*<<< orphan*/  IAA_REGISTER ; 
 int /*<<< orphan*/  IMA ; 
 int MQE_OK ; 
 int MQE_UNEXPECTED_CB_ERR ; 
 int /*<<< orphan*/  UVH_IPI_INT ; 
 int /*<<< orphan*/  XTYPE_CL ; 
 int /*<<< orphan*/  dest_Fixed ; 
 int gru_get_amo_value_head (void*) ; 
 int /*<<< orphan*/  gru_get_tri (void*) ; 
 int /*<<< orphan*/  gru_vset (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_vstore (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_vstore_phys (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gru_wait (void*) ; 
 unsigned long uv_global_gru_mmr_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long uv_hub_ipi_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_message_put_nacked(void *cb, struct gru_message_queue_desc *mqd,
			void *mesg, int lines)
{
	unsigned long m, *val = mesg, gpa, save;
	int ret;

	m = mqd->mq_gpa + (gru_get_amo_value_head(cb) << 6);
	if (lines == 2) {
		gru_vset(cb, m, 0, XTYPE_CL, lines, 1, IMA);
		if (gru_wait(cb) != CBS_IDLE)
			return MQE_UNEXPECTED_CB_ERR;
	}
	gru_vstore(cb, m, gru_get_tri(mesg), XTYPE_CL, lines, 1, IMA);
	if (gru_wait(cb) != CBS_IDLE)
		return MQE_UNEXPECTED_CB_ERR;

	if (!mqd->interrupt_vector)
		return MQE_OK;

	/*
	 * Send a cross-partition interrupt to the SSI that contains the target
	 * message queue. Normally, the interrupt is automatically delivered by
	 * hardware but some error conditions require explicit delivery.
	 * Use the GRU to deliver the interrupt. Otherwise partition failures
	 * could cause unrecovered errors.
	 */
	gpa = uv_global_gru_mmr_address(mqd->interrupt_pnode, UVH_IPI_INT);
	save = *val;
	*val = uv_hub_ipi_value(mqd->interrupt_apicid, mqd->interrupt_vector,
				dest_Fixed);
	gru_vstore_phys(cb, gpa, gru_get_tri(mesg), IAA_REGISTER, IMA);
	ret = gru_wait(cb);
	*val = save;
	if (ret != CBS_IDLE)
		return MQE_UNEXPECTED_CB_ERR;
	return MQE_OK;
}