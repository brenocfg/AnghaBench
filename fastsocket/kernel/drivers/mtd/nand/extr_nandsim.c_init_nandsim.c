#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ totsz; unsigned long long pgsz; unsigned long long oobsz; int secsz; unsigned long long pgszoob; unsigned long long pgnum; unsigned long long secshift; unsigned long long pgshift; unsigned long long oobshift; int pgsec; int secszoob; int pgaddrbytes; int secaddrbytes; scalar_t__ totszoob; } ;
struct TYPE_5__ {int /*<<< orphan*/  byte; } ;
struct nandsim {int busw; int options; int nbparts; TYPE_2__ geom; TYPE_1__ buf; TYPE_4__* partitions; } ;
struct nand_chip {int options; unsigned long long page_shift; scalar_t__ chip_delay; scalar_t__ priv; } ;
struct mtd_info {scalar_t__ size; unsigned long long writesize; unsigned long long oobsize; int erasesize; scalar_t__ priv; } ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ offset; void* name; } ;
struct TYPE_7__ {scalar_t__ id; int options; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAND_BUSWIDTH_16 ; 
 int NAND_NO_AUTOINCR ; 
 int /*<<< orphan*/  NS_ERR (char*,...) ; 
 scalar_t__ NS_IS_INITIALIZED (struct nandsim*) ; 
 int /*<<< orphan*/  NS_WARN (char*) ; 
 int OPT_AUTOINCR ; 
 int OPT_PAGE2048 ; 
 int OPT_PAGE256 ; 
 int OPT_PAGE512 ; 
 int OPT_PAGE512_8BIT ; 
 int OPT_SMALLPAGE ; 
 int alloc_device (struct nandsim*) ; 
 unsigned long long divide (scalar_t__,unsigned long long) ; 
 void* ffs (scalar_t__) ; 
 int /*<<< orphan*/  free_device (struct nandsim*) ; 
 void* get_partition_name (int) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* nand_flash_ids ; 
 scalar_t__* parts ; 
 int parts_num ; 
 int /*<<< orphan*/  printk (char*,unsigned long long) ; 
 scalar_t__ second_id_byte ; 

__attribute__((used)) static int init_nandsim(struct mtd_info *mtd)
{
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;
	struct nandsim   *ns   = (struct nandsim *)(chip->priv);
	int i, ret = 0;
	uint64_t remains;
	uint64_t next_offset;

	if (NS_IS_INITIALIZED(ns)) {
		NS_ERR("init_nandsim: nandsim is already initialized\n");
		return -EIO;
	}

	/* Force mtd to not do delays */
	chip->chip_delay = 0;

	/* Initialize the NAND flash parameters */
	ns->busw = chip->options & NAND_BUSWIDTH_16 ? 16 : 8;
	ns->geom.totsz    = mtd->size;
	ns->geom.pgsz     = mtd->writesize;
	ns->geom.oobsz    = mtd->oobsize;
	ns->geom.secsz    = mtd->erasesize;
	ns->geom.pgszoob  = ns->geom.pgsz + ns->geom.oobsz;
	ns->geom.pgnum    = divide(ns->geom.totsz, ns->geom.pgsz);
	ns->geom.totszoob = ns->geom.totsz + (uint64_t)ns->geom.pgnum * ns->geom.oobsz;
	ns->geom.secshift = ffs(ns->geom.secsz) - 1;
	ns->geom.pgshift  = chip->page_shift;
	ns->geom.oobshift = ffs(ns->geom.oobsz) - 1;
	ns->geom.pgsec    = ns->geom.secsz / ns->geom.pgsz;
	ns->geom.secszoob = ns->geom.secsz + ns->geom.oobsz * ns->geom.pgsec;
	ns->options = 0;

	if (ns->geom.pgsz == 256) {
		ns->options |= OPT_PAGE256;
	}
	else if (ns->geom.pgsz == 512) {
		ns->options |= (OPT_PAGE512 | OPT_AUTOINCR);
		if (ns->busw == 8)
			ns->options |= OPT_PAGE512_8BIT;
	} else if (ns->geom.pgsz == 2048) {
		ns->options |= OPT_PAGE2048;
	} else {
		NS_ERR("init_nandsim: unknown page size %u\n", ns->geom.pgsz);
		return -EIO;
	}

	if (ns->options & OPT_SMALLPAGE) {
		if (ns->geom.totsz <= (32 << 20)) {
			ns->geom.pgaddrbytes  = 3;
			ns->geom.secaddrbytes = 2;
		} else {
			ns->geom.pgaddrbytes  = 4;
			ns->geom.secaddrbytes = 3;
		}
	} else {
		if (ns->geom.totsz <= (128 << 20)) {
			ns->geom.pgaddrbytes  = 4;
			ns->geom.secaddrbytes = 2;
		} else {
			ns->geom.pgaddrbytes  = 5;
			ns->geom.secaddrbytes = 3;
		}
	}

	/* Fill the partition_info structure */
	if (parts_num > ARRAY_SIZE(ns->partitions)) {
		NS_ERR("too many partitions.\n");
		ret = -EINVAL;
		goto error;
	}
	remains = ns->geom.totsz;
	next_offset = 0;
	for (i = 0; i < parts_num; ++i) {
		uint64_t part_sz = (uint64_t)parts[i] * ns->geom.secsz;

		if (!part_sz || part_sz > remains) {
			NS_ERR("bad partition size.\n");
			ret = -EINVAL;
			goto error;
		}
		ns->partitions[i].name   = get_partition_name(i);
		ns->partitions[i].offset = next_offset;
		ns->partitions[i].size   = part_sz;
		next_offset += ns->partitions[i].size;
		remains -= ns->partitions[i].size;
	}
	ns->nbparts = parts_num;
	if (remains) {
		if (parts_num + 1 > ARRAY_SIZE(ns->partitions)) {
			NS_ERR("too many partitions.\n");
			ret = -EINVAL;
			goto error;
		}
		ns->partitions[i].name   = get_partition_name(i);
		ns->partitions[i].offset = next_offset;
		ns->partitions[i].size   = remains;
		ns->nbparts += 1;
	}

	/* Detect how many ID bytes the NAND chip outputs */
        for (i = 0; nand_flash_ids[i].name != NULL; i++) {
                if (second_id_byte != nand_flash_ids[i].id)
                        continue;
		if (!(nand_flash_ids[i].options & NAND_NO_AUTOINCR))
			ns->options |= OPT_AUTOINCR;
	}

	if (ns->busw == 16)
		NS_WARN("16-bit flashes support wasn't tested\n");

	printk("flash size: %llu MiB\n",
			(unsigned long long)ns->geom.totsz >> 20);
	printk("page size: %u bytes\n",         ns->geom.pgsz);
	printk("OOB area size: %u bytes\n",     ns->geom.oobsz);
	printk("sector size: %u KiB\n",         ns->geom.secsz >> 10);
	printk("pages number: %u\n",            ns->geom.pgnum);
	printk("pages per sector: %u\n",        ns->geom.pgsec);
	printk("bus width: %u\n",               ns->busw);
	printk("bits in sector size: %u\n",     ns->geom.secshift);
	printk("bits in page size: %u\n",       ns->geom.pgshift);
	printk("bits in OOB size: %u\n",	ns->geom.oobshift);
	printk("flash size with OOB: %llu KiB\n",
			(unsigned long long)ns->geom.totszoob >> 10);
	printk("page address bytes: %u\n",      ns->geom.pgaddrbytes);
	printk("sector address bytes: %u\n",    ns->geom.secaddrbytes);
	printk("options: %#x\n",                ns->options);

	if ((ret = alloc_device(ns)) != 0)
		goto error;

	/* Allocate / initialize the internal buffer */
	ns->buf.byte = kmalloc(ns->geom.pgszoob, GFP_KERNEL);
	if (!ns->buf.byte) {
		NS_ERR("init_nandsim: unable to allocate %u bytes for the internal buffer\n",
			ns->geom.pgszoob);
		ret = -ENOMEM;
		goto error;
	}
	memset(ns->buf.byte, 0xFF, ns->geom.pgszoob);

	return 0;

error:
	free_device(ns);

	return ret;
}