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
typedef  int /*<<< orphan*/  uncond ;
struct ip6t_ip6 {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct ip6t_ip6 const*,struct ip6t_ip6 const*,int) ; 

__attribute__((used)) static inline bool unconditional(const struct ip6t_ip6 *ipv6)
{
	static const struct ip6t_ip6 uncond;

	return memcmp(ipv6, &uncond, sizeof(uncond)) == 0;
}