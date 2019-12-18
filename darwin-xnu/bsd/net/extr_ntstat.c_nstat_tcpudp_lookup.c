#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct inpcbinfo {int dummy; } ;
struct inpcb {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_12__ {int sin6_len; int /*<<< orphan*/  sin6_port; struct in6_addr const sin6_addr; } ;
struct TYPE_9__ {scalar_t__ sin_family; int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_13__ {TYPE_5__ v6; TYPE_2__ v4; } ;
struct TYPE_10__ {int sin6_len; int /*<<< orphan*/  sin6_port; struct in6_addr const sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_8__ {scalar_t__ sin_family; int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_11__ {TYPE_3__ v6; TYPE_1__ v4; } ;
struct TYPE_14__ {TYPE_6__ local; TYPE_4__ remote; } ;
typedef  TYPE_7__ nstat_tcp_add_param ;
typedef  int /*<<< orphan*/ * nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 struct inpcb* in6_pcblookup_hash (struct inpcbinfo*,struct in6_addr*,int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* in_pcblookup_hash (struct inpcbinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nstat_tucookie_alloc (struct inpcb*) ; 

__attribute__((used)) static errno_t
nstat_tcpudp_lookup(
	struct inpcbinfo	*inpinfo,
	const void		*data,
	u_int32_t 		length,
	nstat_provider_cookie_t	*out_cookie)
{
	struct inpcb *inp = NULL;

	// parameter validation
	const nstat_tcp_add_param	*param = (const nstat_tcp_add_param*)data;
	if (length < sizeof(*param))
	{
		return EINVAL;
	}

	// src and dst must match
	if (param->remote.v4.sin_family != 0 &&
		param->remote.v4.sin_family != param->local.v4.sin_family)
	{
		return EINVAL;
	}


	switch (param->local.v4.sin_family)
	{
		case AF_INET:
		{
			if (param->local.v4.sin_len != sizeof(param->local.v4) ||
		  		(param->remote.v4.sin_family != 0 &&
		  		 param->remote.v4.sin_len != sizeof(param->remote.v4)))
		  	{
				return EINVAL;
		  	}

			inp = in_pcblookup_hash(inpinfo, param->remote.v4.sin_addr, param->remote.v4.sin_port,
						param->local.v4.sin_addr, param->local.v4.sin_port, 1, NULL);
		}
		break;

#if INET6
		case AF_INET6:
		{
			union
			{
				const struct in6_addr 	*in6c;
				struct in6_addr			*in6;
			} local, remote;

			if (param->local.v6.sin6_len != sizeof(param->local.v6) ||
		  		(param->remote.v6.sin6_family != 0 &&
				 param->remote.v6.sin6_len != sizeof(param->remote.v6)))
			{
				return EINVAL;
			}

			local.in6c = &param->local.v6.sin6_addr;
			remote.in6c = &param->remote.v6.sin6_addr;

			inp = in6_pcblookup_hash(inpinfo, remote.in6, param->remote.v6.sin6_port,
						local.in6, param->local.v6.sin6_port, 1, NULL);
		}
		break;
#endif

		default:
			return EINVAL;
	}

	if (inp == NULL)
		return ENOENT;

	// At this point we have a ref to the inpcb
	*out_cookie = nstat_tucookie_alloc(inp);
	if (*out_cookie == NULL)
		in_pcb_checkstate(inp, WNT_RELEASE, 0);

	return 0;
}