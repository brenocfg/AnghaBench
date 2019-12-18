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
typedef  int /*<<< orphan*/  tsc ;
struct tc_service_curve {void* m2; int /*<<< orphan*/  d; void* m1; } ;
struct sk_buff {int len; } ;
struct internal_sc {int /*<<< orphan*/  sm2; int /*<<< orphan*/  dx; int /*<<< orphan*/  sm1; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int,int,struct tc_service_curve*) ; 
 int /*<<< orphan*/  dx2d (int /*<<< orphan*/ ) ; 
 void* sm2m (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hfsc_dump_sc(struct sk_buff *skb, int attr, struct internal_sc *sc)
{
	struct tc_service_curve tsc;

	tsc.m1 = sm2m(sc->sm1);
	tsc.d  = dx2d(sc->dx);
	tsc.m2 = sm2m(sc->sm2);
	NLA_PUT(skb, attr, sizeof(tsc), &tsc);

	return skb->len;

 nla_put_failure:
	return -1;
}