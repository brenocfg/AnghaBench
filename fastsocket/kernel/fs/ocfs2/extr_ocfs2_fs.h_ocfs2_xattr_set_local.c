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
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_XATTR_ENTRY_LOCAL ; 

__attribute__((used)) static inline void ocfs2_xattr_set_local(struct ocfs2_xattr_entry *xe,
					 int local)
{
	if (local)
		xe->xe_type |= OCFS2_XATTR_ENTRY_LOCAL;
	else
		xe->xe_type &= ~OCFS2_XATTR_ENTRY_LOCAL;
}