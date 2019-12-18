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
struct ip_vs_timeout_user {int /*<<< orphan*/  udp_timeout; int /*<<< orphan*/  tcp_fin_timeout; int /*<<< orphan*/  tcp_timeout; } ;
struct ip_vs_service {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; TYPE_1__* genlhdr; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IPVS_CMD_ATTR_SERVICE ; 
 int /*<<< orphan*/  IPVS_CMD_ATTR_TIMEOUT_TCP ; 
 int /*<<< orphan*/  IPVS_CMD_ATTR_TIMEOUT_TCP_FIN ; 
 int /*<<< orphan*/  IPVS_CMD_ATTR_TIMEOUT_UDP ; 
#define  IPVS_CMD_GET_CONFIG 130 
#define  IPVS_CMD_GET_INFO 129 
#define  IPVS_CMD_GET_SERVICE 128 
 int IPVS_CMD_NEW_SERVICE ; 
 int IPVS_CMD_SET_CONFIG ; 
 int IPVS_CMD_SET_INFO ; 
 int /*<<< orphan*/  IPVS_INFO_ATTR_CONN_TAB_SIZE ; 
 int /*<<< orphan*/  IPVS_INFO_ATTR_VERSION ; 
 int /*<<< orphan*/  IP_VS_VERSION_CODE ; 
 int /*<<< orphan*/  IS_ERR (struct ip_vs_service*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (struct ip_vs_service*) ; 
 int /*<<< orphan*/  __ip_vs_get_timeouts (struct ip_vs_timeout_user*) ; 
 int /*<<< orphan*/  __ip_vs_mutex ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  ip_vs_conn_tab_size ; 
 int /*<<< orphan*/  ip_vs_genl_family ; 
 int ip_vs_genl_fill_service (struct sk_buff*,struct ip_vs_service*) ; 
 struct ip_vs_service* ip_vs_genl_find_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_service_put (struct ip_vs_service*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ip_vs_genl_get_cmd(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	void *reply;
	int ret, cmd, reply_cmd;

	cmd = info->genlhdr->cmd;

	if (cmd == IPVS_CMD_GET_SERVICE)
		reply_cmd = IPVS_CMD_NEW_SERVICE;
	else if (cmd == IPVS_CMD_GET_INFO)
		reply_cmd = IPVS_CMD_SET_INFO;
	else if (cmd == IPVS_CMD_GET_CONFIG)
		reply_cmd = IPVS_CMD_SET_CONFIG;
	else {
		pr_err("unknown Generic Netlink command\n");
		return -EINVAL;
	}

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	mutex_lock(&__ip_vs_mutex);

	reply = genlmsg_put_reply(msg, info, &ip_vs_genl_family, 0, reply_cmd);
	if (reply == NULL)
		goto nla_put_failure;

	switch (cmd) {
	case IPVS_CMD_GET_SERVICE:
	{
		struct ip_vs_service *svc;

		svc = ip_vs_genl_find_service(info->attrs[IPVS_CMD_ATTR_SERVICE]);
		if (IS_ERR(svc)) {
			ret = PTR_ERR(svc);
			goto out_err;
		} else if (svc) {
			ret = ip_vs_genl_fill_service(msg, svc);
			ip_vs_service_put(svc);
			if (ret)
				goto nla_put_failure;
		} else {
			ret = -ESRCH;
			goto out_err;
		}

		break;
	}

	case IPVS_CMD_GET_CONFIG:
	{
		struct ip_vs_timeout_user t;

		__ip_vs_get_timeouts(&t);
#ifdef CONFIG_IP_VS_PROTO_TCP
		NLA_PUT_U32(msg, IPVS_CMD_ATTR_TIMEOUT_TCP, t.tcp_timeout);
		NLA_PUT_U32(msg, IPVS_CMD_ATTR_TIMEOUT_TCP_FIN,
			    t.tcp_fin_timeout);
#endif
#ifdef CONFIG_IP_VS_PROTO_UDP
		NLA_PUT_U32(msg, IPVS_CMD_ATTR_TIMEOUT_UDP, t.udp_timeout);
#endif

		break;
	}

	case IPVS_CMD_GET_INFO:
		NLA_PUT_U32(msg, IPVS_INFO_ATTR_VERSION, IP_VS_VERSION_CODE);
		NLA_PUT_U32(msg, IPVS_INFO_ATTR_CONN_TAB_SIZE,
			    ip_vs_conn_tab_size);
		break;
	}

	genlmsg_end(msg, reply);
	ret = genlmsg_reply(msg, info);
	goto out;

nla_put_failure:
	pr_err("not enough space in Netlink message\n");
	ret = -EMSGSIZE;

out_err:
	nlmsg_free(msg);
out:
	mutex_unlock(&__ip_vs_mutex);

	return ret;
}