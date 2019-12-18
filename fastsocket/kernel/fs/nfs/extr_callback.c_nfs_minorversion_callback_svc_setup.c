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
typedef  int /*<<< orphan*/  u32 ;
struct svc_serv {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int nfs_minorversion_callback_svc_setup(u32 minorversion,
		struct svc_serv *serv, struct rpc_xprt *xprt,
		struct svc_rqst **rqstpp, int (**callback_svc)(void *vrqstp))
{
	return 0;
}