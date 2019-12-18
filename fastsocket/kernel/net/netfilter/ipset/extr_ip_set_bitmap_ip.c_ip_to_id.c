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
typedef  int u32 ;
struct bitmap_ip {int first_ip; int hosts; int /*<<< orphan*/  netmask; } ;

/* Variables and functions */
 int ip_set_hostmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
ip_to_id(const struct bitmap_ip *m, u32 ip)
{
	return ((ip & ip_set_hostmask(m->netmask)) - m->first_ip)/m->hosts;
}