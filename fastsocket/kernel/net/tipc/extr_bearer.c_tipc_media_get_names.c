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
struct sk_buff {int dummy; } ;
struct media {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_MEDIA ; 
 int /*<<< orphan*/  TIPC_MAX_MEDIA_NAME ; 
 int /*<<< orphan*/  TIPC_TLV_MEDIA_NAME ; 
 int TLV_SPACE (int /*<<< orphan*/ ) ; 
 int media_count ; 
 struct media* media_list ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cfg_append_tlv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int) ; 
 int /*<<< orphan*/  tipc_net_lock ; 

struct sk_buff *tipc_media_get_names(void)
{
	struct sk_buff *buf;
	struct media *m_ptr;
	int i;

	buf = tipc_cfg_reply_alloc(MAX_MEDIA * TLV_SPACE(TIPC_MAX_MEDIA_NAME));
	if (!buf)
		return NULL;

	read_lock_bh(&tipc_net_lock);
	for (i = 0, m_ptr = media_list; i < media_count; i++, m_ptr++) {
		tipc_cfg_append_tlv(buf, TIPC_TLV_MEDIA_NAME, m_ptr->name,
				    strlen(m_ptr->name) + 1);
	}
	read_unlock_bh(&tipc_net_lock);
	return buf;
}