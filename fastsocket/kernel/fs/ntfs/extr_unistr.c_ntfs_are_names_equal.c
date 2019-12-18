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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ntfschar ;
typedef  scalar_t__ IGNORE_CASE_BOOL ;

/* Variables and functions */
 scalar_t__ const CASE_SENSITIVE ; 
 int /*<<< orphan*/  ntfs_ucsncasecmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ntfs_ucsncmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

bool ntfs_are_names_equal(const ntfschar *s1, size_t s1_len,
		const ntfschar *s2, size_t s2_len, const IGNORE_CASE_BOOL ic,
		const ntfschar *upcase, const u32 upcase_size)
{
	if (s1_len != s2_len)
		return false;
	if (ic == CASE_SENSITIVE)
		return !ntfs_ucsncmp(s1, s2, s1_len);
	return !ntfs_ucsncasecmp(s1, s2, s1_len, upcase, upcase_size);
}