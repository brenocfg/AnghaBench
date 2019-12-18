#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  work; scalar_t__ result; int /*<<< orphan*/ * iocb; scalar_t__ error; scalar_t__ size; scalar_t__ offset; scalar_t__ flag; struct inode* inode; } ;
typedef  TYPE_1__ ext4_io_end_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_end_aio_dio_work ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_io_end_t *ext4_init_io_end (struct inode *inode)
{
	ext4_io_end_t *io = NULL;

	io = kmalloc(sizeof(*io), GFP_NOFS);

	if (io) {
		igrab(inode);
		io->inode = inode;
		io->flag = 0;
		io->offset = 0;
		io->size = 0;
		io->error = 0;
		io->iocb = NULL;
		io->result = 0;
		INIT_WORK(&io->work, ext4_end_aio_dio_work);
		INIT_LIST_HEAD(&io->list);
	}

	return io;
}