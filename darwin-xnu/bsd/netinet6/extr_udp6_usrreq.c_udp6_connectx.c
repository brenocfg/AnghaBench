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
typedef  int /*<<< orphan*/  user_ssize_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  sae_connid_t ;
typedef  int /*<<< orphan*/  sae_associd_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int udp_connectx_common (struct socket*,int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udp6_connectx(struct socket *so, struct sockaddr *src,
    struct sockaddr *dst, struct proc *p, uint32_t ifscope,
    sae_associd_t aid, sae_connid_t *pcid, uint32_t flags, void *arg,
    uint32_t arglen, struct uio *uio, user_ssize_t *bytes_written)
{
	return (udp_connectx_common(so, AF_INET6, src, dst,
	    p, ifscope, aid, pcid, flags, arg, arglen, uio, bytes_written));
}