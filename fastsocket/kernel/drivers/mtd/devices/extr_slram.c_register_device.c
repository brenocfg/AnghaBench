#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mtd_info {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ slram_priv_t ;
struct TYPE_8__ {TYPE_5__* mtdinfo; struct TYPE_8__* next; } ;
typedef  TYPE_2__ slram_mtd_list_t ;
struct TYPE_9__ {char* name; unsigned long size; int writesize; struct TYPE_9__* priv; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  unpoint; int /*<<< orphan*/  point; int /*<<< orphan*/  erase; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  E (char*) ; 
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_RAM ; 
 int /*<<< orphan*/  MTD_RAM ; 
 int /*<<< orphan*/  SLRAM_BLK_SZ ; 
 int /*<<< orphan*/  T (char*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ add_mtd_device (TYPE_5__*) ; 
 int /*<<< orphan*/  ioremap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slram_erase ; 
 TYPE_2__* slram_mtdlist ; 
 int /*<<< orphan*/  slram_point ; 
 int /*<<< orphan*/  slram_read ; 
 int /*<<< orphan*/  slram_unpoint ; 
 int /*<<< orphan*/  slram_write ; 

__attribute__((used)) static int register_device(char *name, unsigned long start, unsigned long length)
{
	slram_mtd_list_t **curmtd;

	curmtd = &slram_mtdlist;
	while (*curmtd) {
		curmtd = &(*curmtd)->next;
	}

	*curmtd = kmalloc(sizeof(slram_mtd_list_t), GFP_KERNEL);
	if (!(*curmtd)) {
		E("slram: Cannot allocate new MTD device.\n");
		return(-ENOMEM);
	}
	(*curmtd)->mtdinfo = kzalloc(sizeof(struct mtd_info), GFP_KERNEL);
	(*curmtd)->next = NULL;

	if ((*curmtd)->mtdinfo)	{
		(*curmtd)->mtdinfo->priv =
			kzalloc(sizeof(slram_priv_t), GFP_KERNEL);

		if (!(*curmtd)->mtdinfo->priv) {
			kfree((*curmtd)->mtdinfo);
			(*curmtd)->mtdinfo = NULL;
		}
	}

	if (!(*curmtd)->mtdinfo) {
		E("slram: Cannot allocate new MTD device.\n");
		return(-ENOMEM);
	}

	if (!(((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start =
				ioremap(start, length))) {
		E("slram: ioremap failed\n");
		return -EIO;
	}
	((slram_priv_t *)(*curmtd)->mtdinfo->priv)->end =
		((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start + length;


	(*curmtd)->mtdinfo->name = name;
	(*curmtd)->mtdinfo->size = length;
	(*curmtd)->mtdinfo->flags = MTD_CAP_RAM;
        (*curmtd)->mtdinfo->erase = slram_erase;
	(*curmtd)->mtdinfo->point = slram_point;
	(*curmtd)->mtdinfo->unpoint = slram_unpoint;
	(*curmtd)->mtdinfo->read = slram_read;
	(*curmtd)->mtdinfo->write = slram_write;
	(*curmtd)->mtdinfo->owner = THIS_MODULE;
	(*curmtd)->mtdinfo->type = MTD_RAM;
	(*curmtd)->mtdinfo->erasesize = SLRAM_BLK_SZ;
	(*curmtd)->mtdinfo->writesize = 1;

	if (add_mtd_device((*curmtd)->mtdinfo))	{
		E("slram: Failed to register new device\n");
		iounmap(((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start);
		kfree((*curmtd)->mtdinfo->priv);
		kfree((*curmtd)->mtdinfo);
		return(-EAGAIN);
	}
	T("slram: Registered device %s from %luKiB to %luKiB\n", name,
			(start / 1024), ((start + length) / 1024));
	T("slram: Mapped from 0x%p to 0x%p\n",
			((slram_priv_t *)(*curmtd)->mtdinfo->priv)->start,
			((slram_priv_t *)(*curmtd)->mtdinfo->priv)->end);
	return(0);
}