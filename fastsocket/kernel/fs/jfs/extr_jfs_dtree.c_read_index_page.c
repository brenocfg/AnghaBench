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
struct metapage {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PSIZE ; 
 struct metapage* read_metapage (struct inode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int xtLookup (struct inode*,scalar_t__,int,int*,scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct metapage *read_index_page(struct inode *inode, s64 blkno)
{
	int rc;
	s64 xaddr;
	int xflag;
	s32 xlen;

	rc = xtLookup(inode, blkno, 1, &xflag, &xaddr, &xlen, 1);
	if (rc || (xaddr == 0))
		return NULL;

	return read_metapage(inode, xaddr, PSIZE, 1);
}