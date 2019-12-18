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
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;
struct radix_node_head {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 struct rtentry* rt_lookup_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,struct radix_node_head*,int /*<<< orphan*/ ) ; 

struct rtentry *
rt_lookup_coarse(boolean_t lookup_only, struct sockaddr *dst,
    struct sockaddr *netmask, struct radix_node_head *rnh)
{
	return (rt_lookup_common(lookup_only, TRUE, dst, netmask,
	    rnh, IFSCOPE_NONE));
}