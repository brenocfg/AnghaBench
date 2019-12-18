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
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_rec {int dummy; } ;
typedef  enum ocfs2_contig_type { ____Placeholder_ocfs2_contig_type } ocfs2_contig_type ;

/* Variables and functions */
 int CONTIG_NONE ; 

__attribute__((used)) static enum ocfs2_contig_type
ocfs2_refcount_tree_extent_contig(struct ocfs2_extent_tree *et,
				  struct ocfs2_extent_rec *ext,
				  struct ocfs2_extent_rec *insert_rec)
{
	return CONTIG_NONE;
}