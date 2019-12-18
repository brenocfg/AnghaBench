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
typedef  int u8 ;
struct tomoyo_path_info {int dummy; } ;
struct tomoyo_domain_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_MAC_FOR_FILE ; 
 int /*<<< orphan*/  tomoyo_check_flags (struct tomoyo_domain_info*,int /*<<< orphan*/ ) ; 
 int tomoyo_check_single_path_acl2 (struct tomoyo_domain_info*,struct tomoyo_path_info const*,int,int) ; 

__attribute__((used)) static int tomoyo_check_single_path_acl(struct tomoyo_domain_info *domain,
					const u8 type,
					const struct tomoyo_path_info *filename)
{
	if (!tomoyo_check_flags(domain, TOMOYO_MAC_FOR_FILE))
		return 0;
	return tomoyo_check_single_path_acl2(domain, filename, 1 << type, 1);
}