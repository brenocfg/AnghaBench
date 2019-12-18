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
struct ipip_net {int dummy; } ;
struct ip_tunnel {int /*<<< orphan*/  parms; } ;

/* Variables and functions */
 struct ip_tunnel** __ipip_bucket (struct ipip_net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct ip_tunnel **ipip_bucket(struct ipip_net *ipn,
		struct ip_tunnel *t)
{
	return __ipip_bucket(ipn, &t->parms);
}