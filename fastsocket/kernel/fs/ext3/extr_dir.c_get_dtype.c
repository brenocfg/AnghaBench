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

/* Variables and functions */
 unsigned char DT_UNKNOWN ; 
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_FILETYPE ; 
 int EXT3_FT_MAX ; 
 int /*<<< orphan*/  EXT3_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 unsigned char* ext3_filetype_table ; 

__attribute__((used)) static unsigned char get_dtype(struct super_block *sb, int filetype)
{
	if (!EXT3_HAS_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_FILETYPE) ||
	    (filetype >= EXT3_FT_MAX))
		return DT_UNKNOWN;

	return (ext3_filetype_table[filetype]);
}