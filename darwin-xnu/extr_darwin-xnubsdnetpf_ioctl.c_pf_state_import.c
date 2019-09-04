#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_21__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct pfsync_state {scalar_t__ expire; size_t timeout; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; int /*<<< orphan*/  direction; int /*<<< orphan*/  af_gwy; int /*<<< orphan*/  af_lan; int /*<<< orphan*/  proto; int /*<<< orphan*/  tag; int /*<<< orphan*/  proto_variant; TYPE_8__ ext_gwy; TYPE_6__ ext_lan; TYPE_4__ gwy; TYPE_2__ lan; } ;
struct TYPE_22__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_20__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct pf_state_key {int /*<<< orphan*/  flowhash; int /*<<< orphan*/  direction; int /*<<< orphan*/  af_gwy; int /*<<< orphan*/  af_lan; int /*<<< orphan*/  proto; int /*<<< orphan*/  proto_variant; TYPE_7__ ext_gwy; TYPE_5__ ext_lan; TYPE_3__ gwy; TYPE_1__ lan; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_24__ {TYPE_12__* ptr; } ;
struct pf_state {scalar_t__* bytes; scalar_t__* packets; scalar_t__ pfsync_time; void* expire; void* creation; int /*<<< orphan*/ * rt_kif; TYPE_11__ anchor; TYPE_10__ nat_rule; TYPE_9__ rule; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; int /*<<< orphan*/  tag; } ;
struct TYPE_15__ {scalar_t__* timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pf_calc_state_key_flowhash (struct pf_state_key*) ; 
 TYPE_12__ pf_default_rule ; 
 int /*<<< orphan*/  pf_state_peer_from_pfsync (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pf_time_second () ; 

__attribute__((used)) static void
pf_state_import(struct pfsync_state *sp, struct pf_state_key *sk,
    struct pf_state *s)
{
	/* copy to state key */
	sk->lan.addr = sp->lan.addr;
	sk->lan.xport = sp->lan.xport;
	sk->gwy.addr = sp->gwy.addr;
	sk->gwy.xport = sp->gwy.xport;
	sk->ext_lan.addr = sp->ext_lan.addr;
	sk->ext_lan.xport = sp->ext_lan.xport;
	sk->ext_gwy.addr = sp->ext_gwy.addr;
	sk->ext_gwy.xport = sp->ext_gwy.xport;
	sk->proto_variant = sp->proto_variant;
	s->tag = sp->tag;
	sk->proto = sp->proto;
	sk->af_lan = sp->af_lan;
	sk->af_gwy = sp->af_gwy;
	sk->direction = sp->direction;
	sk->flowhash = pf_calc_state_key_flowhash(sk);

	/* copy to state */
	memcpy(&s->id, &sp->id, sizeof (sp->id));
	s->creatorid = sp->creatorid;
	pf_state_peer_from_pfsync(&sp->src, &s->src);
	pf_state_peer_from_pfsync(&sp->dst, &s->dst);

	s->rule.ptr = &pf_default_rule;
	s->nat_rule.ptr = NULL;
	s->anchor.ptr = NULL;
	s->rt_kif = NULL;
	s->creation = pf_time_second();
	s->expire = pf_time_second();
	if (sp->expire > 0)
		s->expire -= pf_default_rule.timeout[sp->timeout] - sp->expire;
	s->pfsync_time = 0;
	s->packets[0] = s->packets[1] = 0;
	s->bytes[0] = s->bytes[1] = 0;
}