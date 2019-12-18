#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ns_mem {int dummy; } ns_mem ;
struct TYPE_6__ {int pgnum; int /*<<< orphan*/  pgszoob; } ;
struct nandsim {void* pages_written; int /*<<< orphan*/  nand_pages_slab; TYPE_3__ geom; TYPE_2__* pages; struct file* cfile; int /*<<< orphan*/  file_buf; } ;
struct file {TYPE_1__* f_op; } ;
struct TYPE_5__ {int /*<<< orphan*/ * byte; } ;
struct TYPE_4__ {int /*<<< orphan*/  aio_write; int /*<<< orphan*/  write; int /*<<< orphan*/  aio_read; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  NS_ERR (char*) ; 
 int O_CREAT ; 
 int O_LARGEFILE ; 
 int O_RDWR ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ cache_file ; 
 int /*<<< orphan*/  filp_close (struct file*,int /*<<< orphan*/ *) ; 
 struct file* filp_open (scalar_t__,int,int) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int alloc_device(struct nandsim *ns)
{
	struct file *cfile;
	int i, err;

	if (cache_file) {
		cfile = filp_open(cache_file, O_CREAT | O_RDWR | O_LARGEFILE, 0600);
		if (IS_ERR(cfile))
			return PTR_ERR(cfile);
		if (!cfile->f_op || (!cfile->f_op->read && !cfile->f_op->aio_read)) {
			NS_ERR("alloc_device: cache file not readable\n");
			err = -EINVAL;
			goto err_close;
		}
		if (!cfile->f_op->write && !cfile->f_op->aio_write) {
			NS_ERR("alloc_device: cache file not writeable\n");
			err = -EINVAL;
			goto err_close;
		}
		ns->pages_written = vmalloc(ns->geom.pgnum);
		if (!ns->pages_written) {
			NS_ERR("alloc_device: unable to allocate pages written array\n");
			err = -ENOMEM;
			goto err_close;
		}
		ns->file_buf = kmalloc(ns->geom.pgszoob, GFP_KERNEL);
		if (!ns->file_buf) {
			NS_ERR("alloc_device: unable to allocate file buf\n");
			err = -ENOMEM;
			goto err_free;
		}
		ns->cfile = cfile;
		memset(ns->pages_written, 0, ns->geom.pgnum);
		return 0;
	}

	ns->pages = vmalloc(ns->geom.pgnum * sizeof(union ns_mem));
	if (!ns->pages) {
		NS_ERR("alloc_device: unable to allocate page array\n");
		return -ENOMEM;
	}
	for (i = 0; i < ns->geom.pgnum; i++) {
		ns->pages[i].byte = NULL;
	}
	ns->nand_pages_slab = kmem_cache_create("nandsim",
						ns->geom.pgszoob, 0, 0, NULL);
	if (!ns->nand_pages_slab) {
		NS_ERR("cache_create: unable to create kmem_cache\n");
		return -ENOMEM;
	}

	return 0;

err_free:
	vfree(ns->pages_written);
err_close:
	filp_close(cfile, NULL);
	return err;
}