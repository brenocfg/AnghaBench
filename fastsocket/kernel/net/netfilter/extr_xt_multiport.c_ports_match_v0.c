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
typedef  unsigned int u_int8_t ;
typedef  scalar_t__ const u_int16_t ;
typedef  enum xt_multiport_flags { ____Placeholder_xt_multiport_flags } xt_multiport_flags ;

/* Variables and functions */
 int XT_MULTIPORT_DESTINATION ; 
 int XT_MULTIPORT_SOURCE ; 

__attribute__((used)) static inline bool
ports_match_v0(const u_int16_t *portlist, enum xt_multiport_flags flags,
	       u_int8_t count, u_int16_t src, u_int16_t dst)
{
	unsigned int i;
	for (i = 0; i < count; i++) {
		if (flags != XT_MULTIPORT_DESTINATION && portlist[i] == src)
			return true;

		if (flags != XT_MULTIPORT_SOURCE && portlist[i] == dst)
			return true;
	}

	return false;
}