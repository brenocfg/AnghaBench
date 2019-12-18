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

/* Variables and functions */
 int PIO_FIFO ; 
 int PIO_STATUS ; 
 int /*<<< orphan*/  REG1 (int) ; 
 void* inb (int) ; 
 int /*<<< orphan*/  insl (int,unsigned char*,int) ; 

__attribute__((used)) static __inline__ int
SYM53C500_pio_read(int fast_pio, int base, unsigned char *request, unsigned int reqlen)
{
	int i;
	int len;	/* current scsi fifo size */

	REG1(base);
	while (reqlen) {
		i = inb(base + PIO_STATUS);
		/* VDEB(printk("pio_status=%x\n", i)); */
		if (i & 0x80) 
			return 0;

		switch (i & 0x1e) {
		default:
		case 0x10:	/* fifo empty */
			len = 0;
			break;
		case 0x0:
			len = 1;
			break; 
		case 0x8:	/* fifo 1/3 full */
			len = 42;
			break;
		case 0xc:	/* fifo 2/3 full */
			len = 84;
			break;
		case 0xe:	/* fifo full */
			len = 128;
			break;
		}

		if ((i & 0x40) && len == 0) { /* fifo empty and interrupt occurred */
			return 0;
		}

		if (len) {
			if (len > reqlen) 
				len = reqlen;

			if (fast_pio && len > 3) {
				insl(base + PIO_FIFO, request, len >> 2);
				request += len & 0xfc; 
				reqlen -= len & 0xfc; 
			} else {
				while (len--) {
					*request++ = inb(base + PIO_FIFO);
					reqlen--;
				}
			} 
		}
	}
	return 0;
}