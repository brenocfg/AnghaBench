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
struct inode {int dummy; } ;
struct extent_map {scalar_t__ start; scalar_t__ len; scalar_t__ block_start; } ;

/* Variables and functions */
 scalar_t__ EXTENT_MAP_LAST_BYTE ; 
 struct extent_map* defrag_lookup_extent (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static bool defrag_check_next_extent(struct inode *inode, struct extent_map *em)
{
	struct extent_map *next;
	bool ret = true;

	/* this is the last extent */
	if (em->start + em->len >= i_size_read(inode))
		return false;

	next = defrag_lookup_extent(inode, em->start + em->len);
	if (!next || next->block_start >= EXTENT_MAP_LAST_BYTE)
		ret = false;

	free_extent_map(next);
	return ret;
}