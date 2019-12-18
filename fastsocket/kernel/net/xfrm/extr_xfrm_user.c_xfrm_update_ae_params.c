#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  use_time; int /*<<< orphan*/  add_time; int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct xfrm_state {void* replay_maxdiff; void* replay_maxage; TYPE_1__ curlft; int /*<<< orphan*/  preplay; int /*<<< orphan*/  replay; } ;
struct xfrm_replay_state {int dummy; } ;
struct xfrm_lifetime_cur {int /*<<< orphan*/  use_time; int /*<<< orphan*/  add_time; int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t XFRMA_ETIMER_THRESH ; 
 size_t XFRMA_LTIME_VAL ; 
 size_t XFRMA_REPLAY_THRESH ; 
 size_t XFRMA_REPLAY_VAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct xfrm_replay_state*,int) ; 
 void* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static void xfrm_update_ae_params(struct xfrm_state *x, struct nlattr **attrs)
{
	struct nlattr *rp = attrs[XFRMA_REPLAY_VAL];
	struct nlattr *lt = attrs[XFRMA_LTIME_VAL];
	struct nlattr *et = attrs[XFRMA_ETIMER_THRESH];
	struct nlattr *rt = attrs[XFRMA_REPLAY_THRESH];

	if (rp) {
		struct xfrm_replay_state *replay;
		replay = nla_data(rp);
		memcpy(&x->replay, replay, sizeof(*replay));
		memcpy(&x->preplay, replay, sizeof(*replay));
	}

	if (lt) {
		struct xfrm_lifetime_cur *ltime;
		ltime = nla_data(lt);
		x->curlft.bytes = ltime->bytes;
		x->curlft.packets = ltime->packets;
		x->curlft.add_time = ltime->add_time;
		x->curlft.use_time = ltime->use_time;
	}

	if (et)
		x->replay_maxage = nla_get_u32(et);

	if (rt)
		x->replay_maxdiff = nla_get_u32(rt);
}