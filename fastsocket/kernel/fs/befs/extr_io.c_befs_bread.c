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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  befs_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  befs_debug (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 

struct buffer_head *
befs_bread(struct super_block *sb, befs_blocknr_t block)
{
	struct buffer_head *bh = NULL;

	befs_debug(sb, "---> Enter befs_read() %Lu", block);

	bh = sb_bread(sb, block);

	if (bh == NULL) {
		befs_error(sb, "Failed to read block %lu", block);
		goto error;
	}

	befs_debug(sb, "<--- befs_read()");

	return bh;

      error:
	befs_debug(sb, "<--- befs_read() ERROR");
	return NULL;
}