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
struct dlm_message {void* m_result; void* m_asts; void* m_bastmode; void* m_rqmode; void* m_grmode; void* m_status; void* m_hash; void* m_lvbseq; void* m_flags; void* m_sbflags; void* m_exflags; void* m_parent_remid; void* m_parent_lkid; void* m_remid; void* m_lkid; void* m_pid; void* m_nodeid; void* m_type; int /*<<< orphan*/  m_header; } ;

/* Variables and functions */
 void* cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  header_out (int /*<<< orphan*/ *) ; 
 void* to_dlm_errno (void*) ; 

void dlm_message_out(struct dlm_message *ms)
{
	header_out(&ms->m_header);

	ms->m_type		= cpu_to_le32(ms->m_type);
	ms->m_nodeid		= cpu_to_le32(ms->m_nodeid);
	ms->m_pid		= cpu_to_le32(ms->m_pid);
	ms->m_lkid		= cpu_to_le32(ms->m_lkid);
	ms->m_remid		= cpu_to_le32(ms->m_remid);
	ms->m_parent_lkid	= cpu_to_le32(ms->m_parent_lkid);
	ms->m_parent_remid	= cpu_to_le32(ms->m_parent_remid);
	ms->m_exflags		= cpu_to_le32(ms->m_exflags);
	ms->m_sbflags		= cpu_to_le32(ms->m_sbflags);
	ms->m_flags		= cpu_to_le32(ms->m_flags);
	ms->m_lvbseq		= cpu_to_le32(ms->m_lvbseq);
	ms->m_hash		= cpu_to_le32(ms->m_hash);
	ms->m_status		= cpu_to_le32(ms->m_status);
	ms->m_grmode		= cpu_to_le32(ms->m_grmode);
	ms->m_rqmode		= cpu_to_le32(ms->m_rqmode);
	ms->m_bastmode		= cpu_to_le32(ms->m_bastmode);
	ms->m_asts		= cpu_to_le32(ms->m_asts);
	ms->m_result		= cpu_to_le32(to_dlm_errno(ms->m_result));
}