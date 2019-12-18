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
struct swsusp_info {int /*<<< orphan*/  version_code; int /*<<< orphan*/  uts; } ;
struct new_utsname {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_VERSION_CODE ; 
 int /*<<< orphan*/  init_utsname () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_header_complete(struct swsusp_info *info)
{
	memcpy(&info->uts, init_utsname(), sizeof(struct new_utsname));
	info->version_code = LINUX_VERSION_CODE;
	return 0;
}