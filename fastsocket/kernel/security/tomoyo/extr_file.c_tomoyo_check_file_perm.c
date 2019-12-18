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
typedef  int /*<<< orphan*/  u8 ;
struct tomoyo_path_info {char const* name; } ;
struct tomoyo_domain_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_MAC_FOR_FILE ; 
 int tomoyo_check_file_perm2 (struct tomoyo_domain_info*,struct tomoyo_path_info*,int /*<<< orphan*/  const,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tomoyo_check_flags (struct tomoyo_domain_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_fill_path_info (struct tomoyo_path_info*) ; 

int tomoyo_check_file_perm(struct tomoyo_domain_info *domain,
			   const char *filename, const u8 perm)
{
	struct tomoyo_path_info name;
	const u8 mode = tomoyo_check_flags(domain, TOMOYO_MAC_FOR_FILE);

	if (!mode)
		return 0;
	name.name = filename;
	tomoyo_fill_path_info(&name);
	return tomoyo_check_file_perm2(domain, &name, perm, "sysctl", mode);
}