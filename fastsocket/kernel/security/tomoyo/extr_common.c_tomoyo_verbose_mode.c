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
struct tomoyo_domain_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_VERBOSE ; 
 scalar_t__ tomoyo_check_flags (struct tomoyo_domain_info const*,int /*<<< orphan*/ ) ; 

bool tomoyo_verbose_mode(const struct tomoyo_domain_info *domain)
{
	return tomoyo_check_flags(domain, TOMOYO_VERBOSE) != 0;
}