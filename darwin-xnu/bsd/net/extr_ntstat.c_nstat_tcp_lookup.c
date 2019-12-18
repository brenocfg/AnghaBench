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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  nstat_tcpudp_lookup (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcbinfo ; 

__attribute__((used)) static errno_t
nstat_tcp_lookup(
	const void				*data,
	u_int32_t 				length,
	nstat_provider_cookie_t	*out_cookie)
{
	return nstat_tcpudp_lookup(&tcbinfo, data, length, out_cookie);
}