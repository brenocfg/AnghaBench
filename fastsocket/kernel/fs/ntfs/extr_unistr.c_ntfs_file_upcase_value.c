#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ntfschar ;
struct TYPE_3__ {int /*<<< orphan*/  file_name_length; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_1__ FILE_NAME_ATTR ;

/* Variables and functions */
 int /*<<< orphan*/  ntfs_upcase_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

void ntfs_file_upcase_value(FILE_NAME_ATTR *file_name_attr,
		const ntfschar *upcase, const u32 upcase_len)
{
	ntfs_upcase_name((ntfschar*)&file_name_attr->file_name,
			file_name_attr->file_name_length, upcase, upcase_len);
}