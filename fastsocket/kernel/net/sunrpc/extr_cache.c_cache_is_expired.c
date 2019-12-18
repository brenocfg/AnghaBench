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
struct cache_head {scalar_t__ expiry_time; scalar_t__ last_refresh; } ;
struct cache_detail {scalar_t__ flush_time; } ;

/* Variables and functions */
 scalar_t__ seconds_since_boot () ; 

__attribute__((used)) static inline int cache_is_expired(struct cache_detail *detail, struct cache_head *h)
{
	return  (h->expiry_time < seconds_since_boot()) ||
		(detail->flush_time > h->last_refresh);
}