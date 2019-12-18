#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct media {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bearer {TYPE_1__ publ; struct media* media; scalar_t__ active; } ;

/* Variables and functions */
 int MAX_BEARERS ; 
 int /*<<< orphan*/  TIPC_MAX_BEARER_NAME ; 
 int /*<<< orphan*/  TIPC_TLV_BEARER_NAME ; 
 int TLV_SPACE (int /*<<< orphan*/ ) ; 
 int media_count ; 
 struct media* media_list ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 struct bearer* tipc_bearers ; 
 int /*<<< orphan*/  tipc_cfg_append_tlv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int) ; 
 int /*<<< orphan*/  tipc_net_lock ; 

struct sk_buff *tipc_bearer_get_names(void)
{
	struct sk_buff *buf;
	struct media *m_ptr;
	struct bearer *b_ptr;
	int i, j;

	buf = tipc_cfg_reply_alloc(MAX_BEARERS * TLV_SPACE(TIPC_MAX_BEARER_NAME));
	if (!buf)
		return NULL;

	read_lock_bh(&tipc_net_lock);
	for (i = 0, m_ptr = media_list; i < media_count; i++, m_ptr++) {
		for (j = 0; j < MAX_BEARERS; j++) {
			b_ptr = &tipc_bearers[j];
			if (b_ptr->active && (b_ptr->media == m_ptr)) {
				tipc_cfg_append_tlv(buf, TIPC_TLV_BEARER_NAME,
						    b_ptr->publ.name,
						    strlen(b_ptr->publ.name) + 1);
			}
		}
	}
	read_unlock_bh(&tipc_net_lock);
	return buf;
}