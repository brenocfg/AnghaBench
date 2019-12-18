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
typedef  scalar_t__ le32 ;
typedef  scalar_t__ NTFS_RECORD_TYPE ;

/* Variables and functions */

__attribute__((used)) static inline bool __ntfs_is_magic(le32 x, NTFS_RECORD_TYPE r)
{
	return (x == r);
}