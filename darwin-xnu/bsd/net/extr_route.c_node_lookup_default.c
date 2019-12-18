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
struct radix_node_head {struct radix_node* (* rnh_lookup ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct radix_node_head*) ;} ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  sin6_def ; 
 int /*<<< orphan*/  sin_def ; 
 struct radix_node* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct radix_node_head*) ; 
 struct radix_node* stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct radix_node_head*) ; 

__attribute__((used)) static struct radix_node *
node_lookup_default(int af)
{
	struct radix_node_head *rnh;

	VERIFY(af == AF_INET || af == AF_INET6);
	rnh = rt_tables[af];

	return (af == AF_INET ? rnh->rnh_lookup(&sin_def, NULL, rnh) :
	    rnh->rnh_lookup(&sin6_def, NULL, rnh));
}