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
typedef  int /*<<< orphan*/  u8 ;
struct jr3_pci_subdev_private {int dummy; } ;
struct jr3_pci_dev_private {int n_channels; TYPE_3__* iobase; } ;
struct comedi_device {TYPE_1__* subdevices; struct jr3_pci_dev_private* private; } ;
struct TYPE_6__ {TYPE_2__* channel; } ;
struct TYPE_5__ {int /*<<< orphan*/ * program_high; int /*<<< orphan*/ * program_low; } ;
struct TYPE_4__ {struct jr3_pci_subdev_private* private; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int,unsigned int) ; 
 scalar_t__ read_idm_word (int /*<<< orphan*/  const*,size_t,int*,unsigned int*) ; 
 int /*<<< orphan*/  set_u16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int jr3_download_firmware(struct comedi_device *dev, const u8 * data,
				 size_t size)
{
	/*
	 * IDM file format is:
	 *   { count, address, data <count> } *
	 *   ffff
	 */
	int result, more, pos, OK;

	result = 0;
	more = 1;
	pos = 0;
	OK = 0;
	while (more) {
		unsigned int count, addr;

		more = more && read_idm_word(data, size, &pos, &count);
		if (more && count == 0xffff) {
			OK = 1;
			break;
		}
		more = more && read_idm_word(data, size, &pos, &addr);
		while (more && count > 0) {
			unsigned int dummy;
			more = more && read_idm_word(data, size, &pos, &dummy);
			count--;
		}
	}

	if (!OK) {
		result = -ENODATA;
	} else {
		int i;
		struct jr3_pci_dev_private *p = dev->private;

		for (i = 0; i < p->n_channels; i++) {
			struct jr3_pci_subdev_private *sp;

			sp = dev->subdevices[i].private;
			more = 1;
			pos = 0;
			while (more) {
				unsigned int count, addr;
				more = more
				    && read_idm_word(data, size, &pos, &count);
				if (more && count == 0xffff) {
					break;
				}
				more = more
				    && read_idm_word(data, size, &pos, &addr);
				printk("Loading#%d %4.4x bytes at %4.4x\n", i,
				       count, addr);
				while (more && count > 0) {
					if (addr & 0x4000) {
						/*  16 bit data, never seen in real life!! */
						unsigned int data1;

						more = more
						    && read_idm_word(data,
								     size, &pos,
								     &data1);
						count--;
						/* printk("jr3_data, not tested\n"); */
						/* jr3[addr + 0x20000 * pnum] = data1; */
					} else {
						/*   Download 24 bit program */
						unsigned int data1, data2;

						more = more
						    && read_idm_word(data,
								     size, &pos,
								     &data1);
						more = more
						    && read_idm_word(data, size,
								     &pos,
								     &data2);
						count -= 2;
						if (more) {
							set_u16(&p->
								iobase->channel
								[i].program_low
								[addr], data1);
							udelay(1);
							set_u16(&p->
								iobase->channel
								[i].program_high
								[addr], data2);
							udelay(1);

						}
					}
					addr++;
				}
			}
		}
	}
	return result;
}