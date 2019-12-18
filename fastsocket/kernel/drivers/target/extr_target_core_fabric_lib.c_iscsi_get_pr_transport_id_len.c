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
typedef  int u32 ;
struct t10_pr_registration {scalar_t__ isid_present_at_reg; } ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {int /*<<< orphan*/  nacl_sess_lock; int /*<<< orphan*/  initiatorname; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

u32 iscsi_get_pr_transport_id_len(
	struct se_portal_group *se_tpg,
	struct se_node_acl *se_nacl,
	struct t10_pr_registration *pr_reg,
	int *format_code)
{
	u32 len = 0, padding = 0;

	spin_lock_irq(&se_nacl->nacl_sess_lock);
	len = strlen(se_nacl->initiatorname);
	/*
	 * Add extra byte for NULL terminator
	 */
	len++;
	/*
	 * If there is ISID present with the registration, use format code:
	 * 01b: iSCSI Initiator port TransportID format
	 *
	 * If there is not an active iSCSI session, use format code:
	 * 00b: iSCSI Initiator device TransportID format
	 */
	if (pr_reg->isid_present_at_reg) {
		len += 5; /* For ",i,0x" ASCII separator */
		len += 7; /* For iSCSI Initiator Session ID + Null terminator */
		*format_code = 1;
	} else
		*format_code = 0;
	spin_unlock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * The ADDITIONAL LENGTH field specifies the number of bytes that follow
	 * in the TransportID. The additional length shall be at least 20 and
	 * shall be a multiple of four.
	 */
	padding = ((-len) & 3);
	if (padding != 0)
		len += padding;
	/*
	 * Increment value for total payload + header length for
	 * full status descriptor
	 */
	len += 4;

	return len;
}