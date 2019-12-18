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
struct ipt_ip {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct ipt_ip const*,struct ipt_ip const*,int) ; 

__attribute__((used)) static inline bool unconditional(const struct ipt_ip *ip)
{
	static const struct ipt_ip uncond;

	return memcmp(ip, &uncond, sizeof(uncond)) == 0;
#undef FWINV
}