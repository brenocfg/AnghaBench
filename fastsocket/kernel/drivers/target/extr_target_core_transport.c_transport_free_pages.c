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
struct se_cmd {int se_cmd_flags; scalar_t__ t_bidi_data_nents; int /*<<< orphan*/ * t_bidi_data_sg; scalar_t__ t_data_nents; int /*<<< orphan*/ * t_data_sg; } ;

/* Variables and functions */
 int SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC ; 
 int /*<<< orphan*/  transport_free_sgl (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void transport_free_pages(struct se_cmd *cmd)
{
	if (cmd->se_cmd_flags & SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC)
		return;

	transport_free_sgl(cmd->t_data_sg, cmd->t_data_nents);
	cmd->t_data_sg = NULL;
	cmd->t_data_nents = 0;

	transport_free_sgl(cmd->t_bidi_data_sg, cmd->t_bidi_data_nents);
	cmd->t_bidi_data_sg = NULL;
	cmd->t_bidi_data_nents = 0;
}