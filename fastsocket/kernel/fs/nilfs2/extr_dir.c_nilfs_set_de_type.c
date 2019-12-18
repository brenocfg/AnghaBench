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
struct nilfs_dir_entry {int /*<<< orphan*/  file_type; } ;
struct inode {size_t i_mode; } ;
typedef  size_t mode_t ;

/* Variables and functions */
 size_t S_IFMT ; 
 size_t S_SHIFT ; 
 int /*<<< orphan*/ * nilfs_type_by_mode ; 

__attribute__((used)) static void nilfs_set_de_type(struct nilfs_dir_entry *de, struct inode *inode)
{
	mode_t mode = inode->i_mode;

	de->file_type = nilfs_type_by_mode[(mode & S_IFMT)>>S_SHIFT];
}