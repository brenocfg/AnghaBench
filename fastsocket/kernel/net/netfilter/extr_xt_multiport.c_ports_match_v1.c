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
typedef  scalar_t__ u_int16_t ;
struct xt_multiport_v1 {unsigned int count; scalar_t__* ports; scalar_t__ flags; int invert; scalar_t__* pflags; } ;

/* Variables and functions */
 scalar_t__ XT_MULTIPORT_DESTINATION ; 
 scalar_t__ XT_MULTIPORT_EITHER ; 
 scalar_t__ XT_MULTIPORT_SOURCE ; 
 int /*<<< orphan*/  duprintf (char*,scalar_t__,...) ; 

__attribute__((used)) static inline bool
ports_match_v1(const struct xt_multiport_v1 *minfo,
	       u_int16_t src, u_int16_t dst)
{
	unsigned int i;
	u_int16_t s, e;

	for (i = 0; i < minfo->count; i++) {
		s = minfo->ports[i];

		if (minfo->pflags[i]) {
			/* range port matching */
			e = minfo->ports[++i];
			duprintf("src or dst matches with %d-%d?\n", s, e);

			if (minfo->flags == XT_MULTIPORT_SOURCE
			    && src >= s && src <= e)
				return true ^ minfo->invert;
			if (minfo->flags == XT_MULTIPORT_DESTINATION
			    && dst >= s && dst <= e)
				return true ^ minfo->invert;
			if (minfo->flags == XT_MULTIPORT_EITHER
			    && ((dst >= s && dst <= e)
				|| (src >= s && src <= e)))
				return true ^ minfo->invert;
		} else {
			/* exact port matching */
			duprintf("src or dst matches with %d?\n", s);

			if (minfo->flags == XT_MULTIPORT_SOURCE
			    && src == s)
				return true ^ minfo->invert;
			if (minfo->flags == XT_MULTIPORT_DESTINATION
			    && dst == s)
				return true ^ minfo->invert;
			if (minfo->flags == XT_MULTIPORT_EITHER
			    && (src == s || dst == s))
				return true ^ minfo->invert;
		}
	}

	return minfo->invert;
}