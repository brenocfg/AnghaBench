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
struct TYPE_2__ {unsigned long start; int /*<<< orphan*/  end; } ;
struct zorro_dev {TYPE_1__ resource; int /*<<< orphan*/  slotsize; int /*<<< orphan*/  slotaddr; int /*<<< orphan*/  rom; } ;
struct bi_record {unsigned long* data; int tag; } ;
struct ConfigDev {unsigned long cd_BoardSize; scalar_t__ cd_BoardAddr; int /*<<< orphan*/  cd_SlotSize; int /*<<< orphan*/  cd_SlotAddr; int /*<<< orphan*/  cd_Rom; } ;

/* Variables and functions */
#define  BI_AMIGA_AUTOCON 135 
#define  BI_AMIGA_CHIPSET 134 
#define  BI_AMIGA_CHIP_SIZE 133 
#define  BI_AMIGA_ECLOCK 132 
#define  BI_AMIGA_MODEL 131 
#define  BI_AMIGA_PSFREQ 130 
#define  BI_AMIGA_SERPER 129 
#define  BI_AMIGA_VBLANK 128 
 int /*<<< orphan*/  ZORRO_NUM_AUTO ; 
 int amiga_chip_size ; 
 unsigned long amiga_chipset ; 
 unsigned long amiga_eclock ; 
 unsigned long amiga_model ; 
 unsigned char amiga_psfreq ; 
 unsigned char amiga_vblank ; 
 int /*<<< orphan*/  printk (char*) ; 
 struct zorro_dev* zorro_autocon ; 
 int /*<<< orphan*/  zorro_num_autocon ; 

int amiga_parse_bootinfo(const struct bi_record *record)
{
	int unknown = 0;
	const unsigned long *data = record->data;

	switch (record->tag) {
	case BI_AMIGA_MODEL:
		amiga_model = *data;
		break;

	case BI_AMIGA_ECLOCK:
		amiga_eclock = *data;
		break;

	case BI_AMIGA_CHIPSET:
		amiga_chipset = *data;
		break;

	case BI_AMIGA_CHIP_SIZE:
		amiga_chip_size = *(const int *)data;
		break;

	case BI_AMIGA_VBLANK:
		amiga_vblank = *(const unsigned char *)data;
		break;

	case BI_AMIGA_PSFREQ:
		amiga_psfreq = *(const unsigned char *)data;
		break;

	case BI_AMIGA_AUTOCON:
#ifdef CONFIG_ZORRO
		if (zorro_num_autocon < ZORRO_NUM_AUTO) {
			const struct ConfigDev *cd = (struct ConfigDev *)data;
			struct zorro_dev *dev = &zorro_autocon[zorro_num_autocon++];
			dev->rom = cd->cd_Rom;
			dev->slotaddr = cd->cd_SlotAddr;
			dev->slotsize = cd->cd_SlotSize;
			dev->resource.start = (unsigned long)cd->cd_BoardAddr;
			dev->resource.end = dev->resource.start + cd->cd_BoardSize - 1;
		} else
			printk("amiga_parse_bootinfo: too many AutoConfig devices\n");
#endif /* CONFIG_ZORRO */
		break;

	case BI_AMIGA_SERPER:
		/* serial port period: ignored here */
		break;

	default:
		unknown = 1;
	}
	return unknown;
}