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
struct TYPE_11__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct TYPE_8__ {int /*<<< orphan*/  octets; } ;
struct TYPE_9__ {int /*<<< orphan*/  cga_security_level; TYPE_2__ cga_modifier; } ;
struct in6_cgareq_64 {TYPE_5__ cgar_lifetime; TYPE_3__ cgar_cgaprep; int /*<<< orphan*/  cgar_flags; int /*<<< orphan*/  cgar_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  ia6t_pltime; int /*<<< orphan*/  ia6t_vltime; int /*<<< orphan*/  ia6t_preferred; int /*<<< orphan*/  ia6t_expire; } ;
struct TYPE_7__ {int /*<<< orphan*/  octets; } ;
struct TYPE_10__ {int /*<<< orphan*/  cga_security_level; TYPE_1__ cga_modifier; } ;
struct in6_cgareq_32 {TYPE_6__ cgar_lifetime; TYPE_4__ cgar_cgaprep; int /*<<< orphan*/  cgar_flags; int /*<<< orphan*/  cgar_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct in6_cgareq_64*,int) ; 

void
in6_cgareq_32_to_64(struct in6_cgareq_32 *src,
    struct in6_cgareq_64 *dst)
{
	bzero(dst, sizeof (*dst));
	bcopy(src->cgar_name, dst->cgar_name, sizeof (dst->cgar_name));
	dst->cgar_flags = src->cgar_flags;
	bcopy(src->cgar_cgaprep.cga_modifier.octets,
	    dst->cgar_cgaprep.cga_modifier.octets,
	    sizeof (dst->cgar_cgaprep.cga_modifier.octets));
	dst->cgar_cgaprep.cga_security_level =
	    src->cgar_cgaprep.cga_security_level;
	dst->cgar_lifetime.ia6t_expire = src->cgar_lifetime.ia6t_expire;
	dst->cgar_lifetime.ia6t_preferred = src->cgar_lifetime.ia6t_preferred;
	dst->cgar_lifetime.ia6t_vltime = src->cgar_lifetime.ia6t_vltime;
	dst->cgar_lifetime.ia6t_pltime = src->cgar_lifetime.ia6t_pltime;
}