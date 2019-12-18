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
typedef  int /*<<< orphan*/  u32 ;
struct ipmac_telem {int /*<<< orphan*/  timeout; } ;
struct bitmap_ipmac {int dummy; } ;

/* Variables and functions */
 struct ipmac_telem* bitmap_ipmac_elem (struct bitmap_ipmac const*,int /*<<< orphan*/ ) ; 
 int ip_set_timeout_expired (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
bitmap_expired(const struct bitmap_ipmac *map, u32 id)
{
	const struct ipmac_telem *elem = bitmap_ipmac_elem(map, id);

	return ip_set_timeout_expired(elem->timeout);
}