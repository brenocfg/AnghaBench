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
struct rpc_xprt {char const** address_strings; } ;
struct rpc_clnt {struct rpc_xprt* cl_xprt; } ;
typedef  enum rpc_display_format_t { ____Placeholder_rpc_display_format_t } rpc_display_format_t ;

/* Variables and functions */

const char *rpc_peeraddr2str(struct rpc_clnt *clnt,
			     enum rpc_display_format_t format)
{
	struct rpc_xprt *xprt = clnt->cl_xprt;

	if (xprt->address_strings[format] != NULL)
		return xprt->address_strings[format];
	else
		return "unprintable";
}