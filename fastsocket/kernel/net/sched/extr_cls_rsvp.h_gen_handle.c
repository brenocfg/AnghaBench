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
typedef  int u32 ;
struct tcf_proto {struct rsvp_head* root; } ;
struct rsvp_head {int hgenerator; } ;

/* Variables and functions */
 scalar_t__ rsvp_get (struct tcf_proto*,int) ; 

__attribute__((used)) static unsigned gen_handle(struct tcf_proto *tp, unsigned salt)
{
	struct rsvp_head *data = tp->root;
	int i = 0xFFFF;

	while (i-- > 0) {
		u32 h;
		if ((data->hgenerator += 0x10000) == 0)
			data->hgenerator = 0x10000;
		h = data->hgenerator|salt;
		if (rsvp_get(tp, h) == 0)
			return h;
	}
	return 0;
}