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
struct inode {scalar_t__ i_mode; } ;
struct iattr {scalar_t__ ia_mode; int /*<<< orphan*/  ia_valid; } ;
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int gfs2_setattr_simple (struct inode*,struct iattr*) ; 

__attribute__((used)) static int gfs2_set_mode(struct inode *inode, mode_t mode)
{
	int error = 0;

	if (mode != inode->i_mode) {
		struct iattr iattr;

		iattr.ia_valid = ATTR_MODE;
		iattr.ia_mode = mode;

		error = gfs2_setattr_simple(inode, &iattr);
	}

	return error;
}