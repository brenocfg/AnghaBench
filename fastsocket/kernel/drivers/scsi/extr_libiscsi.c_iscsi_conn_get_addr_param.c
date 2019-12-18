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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
 int EINVAL ; 
#define  ISCSI_HOST_PARAM_IPADDRESS 130 
#define  ISCSI_PARAM_CONN_ADDRESS 129 
#define  ISCSI_PARAM_CONN_PORT 128 
 int /*<<< orphan*/ * be16_to_cpu (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ *) ; 

int iscsi_conn_get_addr_param(struct sockaddr_storage *addr,
			      enum iscsi_param param, char *buf)
{
	struct sockaddr_in6 *sin6 = NULL;
	struct sockaddr_in *sin = NULL;
	int len;

	switch (addr->ss_family) {
	case AF_INET:
		sin = (struct sockaddr_in *)addr;
		break;
	case AF_INET6:
		sin6 = (struct sockaddr_in6 *)addr;
		break;
	default:
		return -EINVAL;
	}

	switch (param) {
	case ISCSI_PARAM_CONN_ADDRESS:
	case ISCSI_HOST_PARAM_IPADDRESS:
		if (sin)
			len = sprintf(buf, "%pI4\n", &sin->sin_addr.s_addr);
		else
			len = sprintf(buf, "%pI6\n", &sin6->sin6_addr);
		break;
	case ISCSI_PARAM_CONN_PORT:
		if (sin)
			len = sprintf(buf, "%hu\n", be16_to_cpu(sin->sin_port));
		else
			len = sprintf(buf, "%hu\n",
				      be16_to_cpu(sin6->sin6_port));
		break;
	default:
		return -EINVAL;
	}

	return len;
}