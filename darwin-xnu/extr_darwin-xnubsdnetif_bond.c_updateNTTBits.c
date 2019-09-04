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
typedef  int lacp_actor_partner_state ;

/* Variables and functions */
 int LACP_ACTOR_PARTNER_STATE_AGGREGATION ; 
 int LACP_ACTOR_PARTNER_STATE_LACP_ACTIVITY ; 
 int LACP_ACTOR_PARTNER_STATE_LACP_TIMEOUT ; 
 int LACP_ACTOR_PARTNER_STATE_SYNCHRONIZATION ; 

__attribute__((used)) static __inline__ lacp_actor_partner_state
updateNTTBits(lacp_actor_partner_state s)
{
    return (s & (LACP_ACTOR_PARTNER_STATE_LACP_ACTIVITY
		 | LACP_ACTOR_PARTNER_STATE_LACP_TIMEOUT
		 | LACP_ACTOR_PARTNER_STATE_AGGREGATION
		 | LACP_ACTOR_PARTNER_STATE_SYNCHRONIZATION));
}