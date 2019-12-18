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
struct treepath {int path_length; } ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ILLEGAL_PATH_ELEMENT_OFFSET ; 
 struct buffer_head* PATH_OFFSET_PBUFFER (struct treepath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (struct super_block*,struct buffer_head*) ; 

void pathrelse_and_restore(struct super_block *sb,
			   struct treepath *search_path)
{
	int path_offset = search_path->path_length;

	RFALSE(path_offset < ILLEGAL_PATH_ELEMENT_OFFSET,
	       "clm-4000: invalid path offset");

	while (path_offset > ILLEGAL_PATH_ELEMENT_OFFSET) {
		struct buffer_head *bh;
		bh = PATH_OFFSET_PBUFFER(search_path, path_offset--);
		reiserfs_restore_prepared_buffer(sb, bh);
		brelse(bh);
	}
	search_path->path_length = ILLEGAL_PATH_ELEMENT_OFFSET;
}