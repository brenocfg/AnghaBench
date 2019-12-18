#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  fis_type; } ;
struct TYPE_7__ {TYPE_2__ stp; } ;
struct scu_task_context {TYPE_3__ type; int /*<<< orphan*/  transfer_length_bytes; int /*<<< orphan*/  command_iu_lower; int /*<<< orphan*/  command_iu_upper; } ;
struct scu_sgl_element {int /*<<< orphan*/  address_lower; int /*<<< orphan*/  address_upper; } ;
struct scu_sgl_element_pair {struct scu_sgl_element B; struct scu_sgl_element A; } ;
struct TYPE_5__ {scalar_t__ set; int /*<<< orphan*/  index; } ;
struct isci_stp_request {TYPE_1__ sgl; } ;
struct TYPE_8__ {struct isci_stp_request req; } ;
struct isci_request {struct scu_task_context* tc; TYPE_4__ stp; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int /*<<< orphan*/  FIS_DATA ; 
 scalar_t__ SCU_SGL_ELEMENT_PAIR_A ; 
 int sci_controller_continue_io (struct isci_request*) ; 
 struct scu_sgl_element_pair* to_sgl_element_pair (struct isci_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sci_status sci_stp_request_pio_data_out_trasmit_data_frame(
	struct isci_request *ireq,
	u32 length)
{
	struct isci_stp_request *stp_req = &ireq->stp.req;
	struct scu_task_context *task_context = ireq->tc;
	struct scu_sgl_element_pair *sgl_pair;
	struct scu_sgl_element *current_sgl;

	/* Recycle the TC and reconstruct it for sending out DATA FIS containing
	 * for the data from current_sgl+offset for the input length
	 */
	sgl_pair = to_sgl_element_pair(ireq, stp_req->sgl.index);
	if (stp_req->sgl.set == SCU_SGL_ELEMENT_PAIR_A)
		current_sgl = &sgl_pair->A;
	else
		current_sgl = &sgl_pair->B;

	/* update the TC */
	task_context->command_iu_upper = current_sgl->address_upper;
	task_context->command_iu_lower = current_sgl->address_lower;
	task_context->transfer_length_bytes = length;
	task_context->type.stp.fis_type = FIS_DATA;

	/* send the new TC out. */
	return sci_controller_continue_io(ireq);
}