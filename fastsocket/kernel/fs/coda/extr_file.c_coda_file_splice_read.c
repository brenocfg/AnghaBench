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
struct pipe_inode_info {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
struct coda_file_info {scalar_t__ cfi_magic; struct file* cfi_container; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* splice_read ) (struct file*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_file_info* CODA_FTOC (struct file*) ; 
 scalar_t__ CODA_MAGIC ; 
 int /*<<< orphan*/  default_file_splice_read (struct file*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ; 

__attribute__((used)) static ssize_t
coda_file_splice_read(struct file *coda_file, loff_t *ppos,
		      struct pipe_inode_info *pipe, size_t count,
		      unsigned int flags)
{
	ssize_t (*splice_read)(struct file *, loff_t *,
			       struct pipe_inode_info *, size_t, unsigned int);
	struct coda_file_info *cfi;
	struct file *host_file;

	cfi = CODA_FTOC(coda_file);
	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);
	host_file = cfi->cfi_container;

	splice_read = host_file->f_op->splice_read;
	if (!splice_read)
		splice_read = default_file_splice_read;

	return splice_read(host_file, ppos, pipe, count, flags);
}