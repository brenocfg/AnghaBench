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
struct ocfs2_xattr_entry {int xe_type; } ;

/* Variables and functions */
 int OCFS2_XATTR_TYPE_MASK ; 

__attribute__((used)) static inline void ocfs2_xattr_set_type(struct ocfs2_xattr_entry *xe, int type)
{
	xe->xe_type |= type & OCFS2_XATTR_TYPE_MASK;
}