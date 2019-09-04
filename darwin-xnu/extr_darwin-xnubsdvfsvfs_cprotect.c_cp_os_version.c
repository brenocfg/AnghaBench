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
typedef  int cp_key_os_version_t ;

/* Variables and functions */
 char* osversion ; 
 int parse_os_version (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

cp_key_os_version_t
cp_os_version(void)
{
	static cp_key_os_version_t cp_os_version;

	if (cp_os_version)
		return cp_os_version;

	if (!osversion[0])
		return 0;

	cp_os_version = parse_os_version(osversion);
	if (!cp_os_version) {
		printf("cp_os_version: unable to parse osversion `%s'\n", osversion);
		cp_os_version = 1;
	}

	return cp_os_version;
}