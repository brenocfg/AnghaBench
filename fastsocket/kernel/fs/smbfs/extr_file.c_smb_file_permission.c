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
struct inode {int i_mode; } ;

/* Variables and functions */
 int EACCES ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  VERBOSE (char*,int,int) ; 

__attribute__((used)) static int
smb_file_permission(struct inode *inode, int mask)
{
	int mode = inode->i_mode;
	int error = 0;

	VERBOSE("mode=%x, mask=%x\n", mode, mask);

	/* Look at user permissions */
	mode >>= 6;
	if (mask & ~mode & (MAY_READ | MAY_WRITE | MAY_EXEC))
		error = -EACCES;
	return error;
}