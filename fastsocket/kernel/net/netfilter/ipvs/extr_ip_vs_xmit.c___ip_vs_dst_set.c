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
typedef  void* u32 ;
struct ip_vs_dest {void* dst_cookie; void* dst_rtos; struct dst_entry* dst_cache; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 

__attribute__((used)) static inline void
__ip_vs_dst_set(struct ip_vs_dest *dest, u32 rtos, struct dst_entry *dst,
		u32 dst_cookie)
{
	struct dst_entry *old_dst;

	old_dst = dest->dst_cache;
	dest->dst_cache = dst;
	dest->dst_rtos = rtos;
	dest->dst_cookie = dst_cookie;
	dst_release(old_dst);
}