#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct in6_aliasreq_64 {TYPE_2__ ifra_lifetime; int /*<<< orphan*/  ifra_flags; int /*<<< orphan*/  ifra_prefixmask; int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct in6_aliasreq_32 {TYPE_1__ ifra_lifetime; int /*<<< orphan*/  ifra_flags; int /*<<< orphan*/  ifra_prefixmask; int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct in6_aliasreq_32*,int) ; 

void
in6_aliasreq_64_to_32(struct in6_aliasreq_64 *src, struct in6_aliasreq_32 *dst)
{
	bzero(dst, sizeof (*dst));
	bcopy(src->ifra_name, dst->ifra_name, sizeof (dst->ifra_name));
	dst->ifra_addr = src->ifra_addr;
	dst->ifra_dstaddr = src->ifra_dstaddr;
	dst->ifra_prefixmask = src->ifra_prefixmask;
	dst->ifra_flags = src->ifra_flags;
	dst->ifra_lifetime.ia6t_expire = src->ifra_lifetime.ia6t_expire;
	dst->ifra_lifetime.ia6t_preferred = src->ifra_lifetime.ia6t_preferred;
	dst->ifra_lifetime.ia6t_vltime = src->ifra_lifetime.ia6t_vltime;
	dst->ifra_lifetime.ia6t_pltime = src->ifra_lifetime.ia6t_pltime;
}