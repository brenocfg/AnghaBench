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
struct ocfs2_dx_hinfo {int /*<<< orphan*/  minor_hash; } ;

/* Variables and functions */
 unsigned int __ocfs2_dx_dir_hash_idx (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ocfs2_dx_dir_hash_idx(struct ocfs2_super *osb,
					  struct ocfs2_dx_hinfo *hinfo)
{
	return __ocfs2_dx_dir_hash_idx(osb, hinfo->minor_hash);
}