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
typedef  void* u32 ;
struct se_cmd {int se_cmd_flags; void* t_bidi_data_nents; struct scatterlist* t_bidi_data_sg; void* t_data_nents; struct scatterlist* t_data_sg; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int SCF_OVERFLOW_BIT ; 
 int SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static sense_reason_t
transport_generic_map_mem_to_cmd(struct se_cmd *cmd, struct scatterlist *sgl,
		u32 sgl_count, struct scatterlist *sgl_bidi, u32 sgl_bidi_count)
{
	if (!sgl || !sgl_count)
		return 0;

	/*
	 * Reject SCSI data overflow with map_mem_to_cmd() as incoming
	 * scatterlists already have been set to follow what the fabric
	 * passes for the original expected data transfer length.
	 */
	if (cmd->se_cmd_flags & SCF_OVERFLOW_BIT) {
		pr_warn("Rejecting SCSI DATA overflow for fabric using"
			" SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC\n");
		return TCM_INVALID_CDB_FIELD;
	}

	cmd->t_data_sg = sgl;
	cmd->t_data_nents = sgl_count;

	if (sgl_bidi && sgl_bidi_count) {
		cmd->t_bidi_data_sg = sgl_bidi;
		cmd->t_bidi_data_nents = sgl_bidi_count;
	}
	cmd->se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	return 0;
}