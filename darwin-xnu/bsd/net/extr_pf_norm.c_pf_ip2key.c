#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_1__ v4addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {TYPE_4__ v4addr; } ;
struct pf_fragment {TYPE_2__ fr_dstx; TYPE_5__ fr_srcx; int /*<<< orphan*/  fr_af; int /*<<< orphan*/  fr_id; int /*<<< orphan*/  fr_p; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct ip {TYPE_3__ ip_dst; TYPE_6__ ip_src; int /*<<< orphan*/  ip_id; int /*<<< orphan*/  ip_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void
pf_ip2key(struct pf_fragment *key, struct ip *ip)
{
	key->fr_p = ip->ip_p;
	key->fr_id = ip->ip_id;
	key->fr_af = AF_INET;
	key->fr_srcx.v4addr.s_addr = ip->ip_src.s_addr;
	key->fr_dstx.v4addr.s_addr = ip->ip_dst.s_addr;
}