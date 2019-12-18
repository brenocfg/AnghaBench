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
struct ocfs2_super {int dummy; } ;

/* Variables and functions */
 unsigned int OCFS2_DX_LINK_MAX ; 
 unsigned int OCFS2_LINK_MAX ; 
 scalar_t__ ocfs2_supports_indexed_dirs (struct ocfs2_super*) ; 

__attribute__((used)) static inline unsigned int ocfs2_link_max(struct ocfs2_super *osb)
{
	if (ocfs2_supports_indexed_dirs(osb))
		return OCFS2_DX_LINK_MAX;
	return OCFS2_LINK_MAX;
}