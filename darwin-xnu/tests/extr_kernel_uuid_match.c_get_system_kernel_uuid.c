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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  kuuid_line ;

/* Variables and functions */
 int MAX_LEN ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_parse (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_system_kernel_uuid(uuid_t kuuid) {
	char kuuid_line[MAX_LEN];
	memset(kuuid_line, 0, sizeof(kuuid_line));
	size_t len = sizeof(kuuid_line);
	int ret = sysctlbyname("kern.uuid", kuuid_line, &len, NULL, 0);
	T_ASSERT_POSIX_SUCCESS(ret, "sysctl kern.uuid");

	T_ASSERT_TRUE(uuid_parse(kuuid_line, kuuid) == 0,
			"Parse running kernel uuid");
}