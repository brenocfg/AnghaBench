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
typedef  size_t u32 ;
struct media {size_t priority; int (* enable_bearer ) (TYPE_1__*) ;int /*<<< orphan*/  bcast_addr; scalar_t__ bcast; } ;
struct bearer_name {int media_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct bearer {int active; size_t priority; size_t identity; size_t net_plane; size_t detect_scope; TYPE_1__ publ; int /*<<< orphan*/  link_req; int /*<<< orphan*/  links; int /*<<< orphan*/  cong_links; struct media* media; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t MAX_BEARERS ; 
 size_t TIPC_MAX_LINK_PRI ; 
 size_t TIPC_MEDIA_LINK_PRI ; 
 size_t TIPC_MIN_LINK_PRI ; 
 scalar_t__ TIPC_NET_MODE ; 
 int /*<<< orphan*/  addr_string_fill (char*,size_t) ; 
 int /*<<< orphan*/  bearer_name_validate (char const*,struct bearer_name*) ; 
 int /*<<< orphan*/  in_scope (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*,char const*,int /*<<< orphan*/ ,size_t) ; 
 struct media* media_find (int) ; 
 int /*<<< orphan*/  memset (struct bearer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tipc_addr_domain_valid (size_t) ; 
 struct bearer* tipc_bearers ; 
 int /*<<< orphan*/  tipc_disc_init_link_req (struct bearer*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ tipc_mode ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int tipc_enable_bearer(const char *name, u32 bcast_scope, u32 priority)
{
	struct bearer *b_ptr;
	struct media *m_ptr;
	struct bearer_name b_name;
	char addr_string[16];
	u32 bearer_id;
	u32 with_this_prio;
	u32 i;
	int res = -EINVAL;

	if (tipc_mode != TIPC_NET_MODE) {
		warn("Bearer <%s> rejected, not supported in standalone mode\n",
		     name);
		return -ENOPROTOOPT;
	}
	if (!bearer_name_validate(name, &b_name)) {
		warn("Bearer <%s> rejected, illegal name\n", name);
		return -EINVAL;
	}
	if (!tipc_addr_domain_valid(bcast_scope) ||
	    !in_scope(bcast_scope, tipc_own_addr)) {
		warn("Bearer <%s> rejected, illegal broadcast scope\n", name);
		return -EINVAL;
	}
	if ((priority < TIPC_MIN_LINK_PRI ||
	     priority > TIPC_MAX_LINK_PRI) &&
	    (priority != TIPC_MEDIA_LINK_PRI)) {
		warn("Bearer <%s> rejected, illegal priority\n", name);
		return -EINVAL;
	}

	write_lock_bh(&tipc_net_lock);

	m_ptr = media_find(b_name.media_name);
	if (!m_ptr) {
		warn("Bearer <%s> rejected, media <%s> not registered\n", name,
		     b_name.media_name);
		goto failed;
	}

	if (priority == TIPC_MEDIA_LINK_PRI)
		priority = m_ptr->priority;

restart:
	bearer_id = MAX_BEARERS;
	with_this_prio = 1;
	for (i = MAX_BEARERS; i-- != 0; ) {
		if (!tipc_bearers[i].active) {
			bearer_id = i;
			continue;
		}
		if (!strcmp(name, tipc_bearers[i].publ.name)) {
			warn("Bearer <%s> rejected, already enabled\n", name);
			goto failed;
		}
		if ((tipc_bearers[i].priority == priority) &&
		    (++with_this_prio > 2)) {
			if (priority-- == 0) {
				warn("Bearer <%s> rejected, duplicate priority\n",
				     name);
				goto failed;
			}
			warn("Bearer <%s> priority adjustment required %u->%u\n",
			     name, priority + 1, priority);
			goto restart;
		}
	}
	if (bearer_id >= MAX_BEARERS) {
		warn("Bearer <%s> rejected, bearer limit reached (%u)\n",
		     name, MAX_BEARERS);
		goto failed;
	}

	b_ptr = &tipc_bearers[bearer_id];
	memset(b_ptr, 0, sizeof(struct bearer));

	strcpy(b_ptr->publ.name, name);
	res = m_ptr->enable_bearer(&b_ptr->publ);
	if (res) {
		warn("Bearer <%s> rejected, enable failure (%d)\n", name, -res);
		goto failed;
	}

	b_ptr->identity = bearer_id;
	b_ptr->media = m_ptr;
	b_ptr->net_plane = bearer_id + 'A';
	b_ptr->active = 1;
	b_ptr->detect_scope = bcast_scope;
	b_ptr->priority = priority;
	INIT_LIST_HEAD(&b_ptr->cong_links);
	INIT_LIST_HEAD(&b_ptr->links);
	if (m_ptr->bcast) {
		b_ptr->link_req = tipc_disc_init_link_req(b_ptr, &m_ptr->bcast_addr,
							  bcast_scope, 2);
	}
	spin_lock_init(&b_ptr->publ.lock);
	write_unlock_bh(&tipc_net_lock);
	info("Enabled bearer <%s>, discovery domain %s, priority %u\n",
	     name, addr_string_fill(addr_string, bcast_scope), priority);
	return 0;
failed:
	write_unlock_bh(&tipc_net_lock);
	return res;
}