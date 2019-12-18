#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int vc_rows; int vc_cols; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 int ENXIO ; 
 int HEADER_SIZE ; 
 int fg_console ; 
 int iminor (struct inode*) ; 
 TYPE_1__* vc_cons ; 
 int /*<<< orphan*/  vc_cons_allocated (int) ; 

__attribute__((used)) static int
vcs_size(struct inode *inode)
{
	int size;
	int minor = iminor(inode);
	int currcons = minor & 127;
	struct vc_data *vc;

	if (currcons == 0)
		currcons = fg_console;
	else
		currcons--;
	if (!vc_cons_allocated(currcons))
		return -ENXIO;
	vc = vc_cons[currcons].d;

	size = vc->vc_rows * vc->vc_cols;

	if (minor & 128)
		size = 2*size + HEADER_SIZE;
	return size;
}