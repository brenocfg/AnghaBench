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
struct rtentry {int rt_flags; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int RTF_IFSCOPE ; 
 scalar_t__ SA_DEFAULT (struct sockaddr*) ; 

boolean_t
rt_primary_default(struct rtentry *rt, struct sockaddr *dst)
{
	return (SA_DEFAULT(dst) && !(rt->rt_flags & RTF_IFSCOPE));
}