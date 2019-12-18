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
typedef  scalar_t__ u32 ;
struct tipc_media_addr {int dummy; } ;
struct media {scalar_t__ type_id; int (* send_msg ) (struct sk_buff*,struct tipc_bearer*,struct tipc_media_addr*) ;int (* enable_bearer ) (struct tipc_bearer*) ;void (* disable_bearer ) (struct tipc_bearer*) ;char* (* addr2str ) (struct tipc_media_addr*,char*,int) ;int bcast; scalar_t__ priority; scalar_t__ tolerance; scalar_t__ window; int /*<<< orphan*/  name; int /*<<< orphan*/  bcast_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_MEDIA ; 
 scalar_t__ const TIPC_MAX_LINK_PRI ; 
 scalar_t__ const TIPC_MAX_LINK_TOL ; 
 scalar_t__ const TIPC_MIN_LINK_PRI ; 
 scalar_t__ const TIPC_MIN_LINK_TOL ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  media_count ; 
 struct media* media_list ; 
 int /*<<< orphan*/  media_name_valid (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_media_addr*,int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  warn (char*,char*,...) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int  tipc_register_media(u32 media_type,
			 char *name,
			 int (*enable)(struct tipc_bearer *),
			 void (*disable)(struct tipc_bearer *),
			 int (*send_msg)(struct sk_buff *,
					 struct tipc_bearer *,
					 struct tipc_media_addr *),
			 char *(*addr2str)(struct tipc_media_addr *a,
					   char *str_buf, int str_size),
			 struct tipc_media_addr *bcast_addr,
			 const u32 bearer_priority,
			 const u32 link_tolerance,  /* [ms] */
			 const u32 send_window_limit)
{
	struct media *m_ptr;
	u32 media_id;
	u32 i;
	int res = -EINVAL;

	write_lock_bh(&tipc_net_lock);
	if (!media_list)
		goto exit;

	if (!media_name_valid(name)) {
		warn("Media <%s> rejected, illegal name\n", name);
		goto exit;
	}
	if (!bcast_addr) {
		warn("Media <%s> rejected, no broadcast address\n", name);
		goto exit;
	}
	if ((bearer_priority < TIPC_MIN_LINK_PRI) ||
	    (bearer_priority > TIPC_MAX_LINK_PRI)) {
		warn("Media <%s> rejected, illegal priority (%u)\n", name,
		     bearer_priority);
		goto exit;
	}
	if ((link_tolerance < TIPC_MIN_LINK_TOL) ||
	    (link_tolerance > TIPC_MAX_LINK_TOL)) {
		warn("Media <%s> rejected, illegal tolerance (%u)\n", name,
		     link_tolerance);
		goto exit;
	}

	media_id = media_count++;
	if (media_id >= MAX_MEDIA) {
		warn("Media <%s> rejected, media limit reached (%u)\n", name,
		     MAX_MEDIA);
		media_count--;
		goto exit;
	}
	for (i = 0; i < media_id; i++) {
		if (media_list[i].type_id == media_type) {
			warn("Media <%s> rejected, duplicate type (%u)\n", name,
			     media_type);
			media_count--;
			goto exit;
		}
		if (!strcmp(name, media_list[i].name)) {
			warn("Media <%s> rejected, duplicate name\n", name);
			media_count--;
			goto exit;
		}
	}

	m_ptr = &media_list[media_id];
	m_ptr->type_id = media_type;
	m_ptr->send_msg = send_msg;
	m_ptr->enable_bearer = enable;
	m_ptr->disable_bearer = disable;
	m_ptr->addr2str = addr2str;
	memcpy(&m_ptr->bcast_addr, bcast_addr, sizeof(*bcast_addr));
	m_ptr->bcast = 1;
	strcpy(m_ptr->name, name);
	m_ptr->priority = bearer_priority;
	m_ptr->tolerance = link_tolerance;
	m_ptr->window = send_window_limit;
	dbg("Media <%s> registered\n", name);
	res = 0;
exit:
	write_unlock_bh(&tipc_net_lock);
	return res;
}