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
struct nlattr {int dummy; } ;
struct ip_vs_service_user_kern {scalar_t__ fwmark; int /*<<< orphan*/  af; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  protocol; } ;
struct ip_vs_service {int dummy; } ;
struct ip_vs_dest_user_kern {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; TYPE_1__* genlhdr; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ESRCH ; 
 size_t IPVS_CMD_ATTR_DAEMON ; 
 size_t IPVS_CMD_ATTR_DEST ; 
 size_t IPVS_CMD_ATTR_SERVICE ; 
 int IPVS_CMD_DEL_DAEMON ; 
#define  IPVS_CMD_DEL_DEST 134 
#define  IPVS_CMD_DEL_SERVICE 133 
 int IPVS_CMD_FLUSH ; 
 int IPVS_CMD_NEW_DAEMON ; 
#define  IPVS_CMD_NEW_DEST 132 
#define  IPVS_CMD_NEW_SERVICE 131 
 int IPVS_CMD_SET_CONFIG ; 
#define  IPVS_CMD_SET_DEST 130 
#define  IPVS_CMD_SET_SERVICE 129 
#define  IPVS_CMD_ZERO 128 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MAX ; 
 int /*<<< orphan*/  __ip_vs_mutex ; 
 struct ip_vs_service* __ip_vs_service_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ip_vs_service* __ip_vs_svc_fwm_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int ip_vs_add_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_add_service (struct ip_vs_service_user_kern*,struct ip_vs_service**) ; 
 int /*<<< orphan*/  ip_vs_daemon_policy ; 
 int ip_vs_del_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_del_service (struct ip_vs_service*) ; 
 int ip_vs_edit_dest (struct ip_vs_service*,struct ip_vs_dest_user_kern*) ; 
 int ip_vs_edit_service (struct ip_vs_service*,struct ip_vs_service_user_kern*) ; 
 int ip_vs_flush () ; 
 int ip_vs_genl_del_daemon (struct nlattr**) ; 
 int ip_vs_genl_new_daemon (struct nlattr**) ; 
 int ip_vs_genl_parse_dest (struct ip_vs_dest_user_kern*,int /*<<< orphan*/ ,int) ; 
 int ip_vs_genl_parse_service (struct ip_vs_service_user_kern*,int /*<<< orphan*/ ,int) ; 
 int ip_vs_genl_set_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_service_put (struct ip_vs_service*) ; 
 int ip_vs_zero_all () ; 
 int ip_vs_zero_service (struct ip_vs_service*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_set_cmd(struct sk_buff *skb, struct genl_info *info)
{
	struct ip_vs_service *svc = NULL;
	struct ip_vs_service_user_kern usvc;
	struct ip_vs_dest_user_kern udest;
	int ret = 0, cmd;
	int need_full_svc = 0, need_full_dest = 0;

	cmd = info->genlhdr->cmd;

	mutex_lock(&__ip_vs_mutex);

	if (cmd == IPVS_CMD_FLUSH) {
		ret = ip_vs_flush();
		goto out;
	} else if (cmd == IPVS_CMD_SET_CONFIG) {
		ret = ip_vs_genl_set_config(info->attrs);
		goto out;
	} else if (cmd == IPVS_CMD_NEW_DAEMON ||
		   cmd == IPVS_CMD_DEL_DAEMON) {

		struct nlattr *daemon_attrs[IPVS_DAEMON_ATTR_MAX + 1];

		if (!info->attrs[IPVS_CMD_ATTR_DAEMON] ||
		    nla_parse_nested(daemon_attrs, IPVS_DAEMON_ATTR_MAX,
				     info->attrs[IPVS_CMD_ATTR_DAEMON],
				     ip_vs_daemon_policy)) {
			ret = -EINVAL;
			goto out;
		}

		if (cmd == IPVS_CMD_NEW_DAEMON)
			ret = ip_vs_genl_new_daemon(daemon_attrs);
		else
			ret = ip_vs_genl_del_daemon(daemon_attrs);
		goto out;
	} else if (cmd == IPVS_CMD_ZERO &&
		   !info->attrs[IPVS_CMD_ATTR_SERVICE]) {
		ret = ip_vs_zero_all();
		goto out;
	}

	/* All following commands require a service argument, so check if we
	 * received a valid one. We need a full service specification when
	 * adding / editing a service. Only identifying members otherwise. */
	if (cmd == IPVS_CMD_NEW_SERVICE || cmd == IPVS_CMD_SET_SERVICE)
		need_full_svc = 1;

	ret = ip_vs_genl_parse_service(&usvc,
				       info->attrs[IPVS_CMD_ATTR_SERVICE],
				       need_full_svc);
	if (ret)
		goto out;

	/* Lookup the exact service by <protocol, addr, port> or fwmark */
	if (usvc.fwmark == 0)
		svc = __ip_vs_service_get(usvc.af, usvc.protocol,
					  &usvc.addr, usvc.port);
	else
		svc = __ip_vs_svc_fwm_get(usvc.af, usvc.fwmark);

	/* Unless we're adding a new service, the service must already exist */
	if ((cmd != IPVS_CMD_NEW_SERVICE) && (svc == NULL)) {
		ret = -ESRCH;
		goto out;
	}

	/* Destination commands require a valid destination argument. For
	 * adding / editing a destination, we need a full destination
	 * specification. */
	if (cmd == IPVS_CMD_NEW_DEST || cmd == IPVS_CMD_SET_DEST ||
	    cmd == IPVS_CMD_DEL_DEST) {
		if (cmd != IPVS_CMD_DEL_DEST)
			need_full_dest = 1;

		ret = ip_vs_genl_parse_dest(&udest,
					    info->attrs[IPVS_CMD_ATTR_DEST],
					    need_full_dest);
		if (ret)
			goto out;
	}

	switch (cmd) {
	case IPVS_CMD_NEW_SERVICE:
		if (svc == NULL)
			ret = ip_vs_add_service(&usvc, &svc);
		else
			ret = -EEXIST;
		break;
	case IPVS_CMD_SET_SERVICE:
		ret = ip_vs_edit_service(svc, &usvc);
		break;
	case IPVS_CMD_DEL_SERVICE:
		ret = ip_vs_del_service(svc);
		break;
	case IPVS_CMD_NEW_DEST:
		ret = ip_vs_add_dest(svc, &udest);
		break;
	case IPVS_CMD_SET_DEST:
		ret = ip_vs_edit_dest(svc, &udest);
		break;
	case IPVS_CMD_DEL_DEST:
		ret = ip_vs_del_dest(svc, &udest);
		break;
	case IPVS_CMD_ZERO:
		ret = ip_vs_zero_service(svc);
		break;
	default:
		ret = -EINVAL;
	}

out:
	if (svc)
		ip_vs_service_put(svc);
	mutex_unlock(&__ip_vs_mutex);

	return ret;
}