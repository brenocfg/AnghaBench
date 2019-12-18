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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct udc {int /*<<< orphan*/  rxfifo; } ;

/* Variables and functions */
 int UDC_BITS_PER_BYTE ; 
 int UDC_BYTE_MASK ; 
 int UDC_DWORD_BYTES ; 
 int /*<<< orphan*/  VDBG (struct udc*,char*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udc_rxfifo_read_bytes(struct udc *dev, u8 *buf, int bytes)
{
	int i, j;
	u32 tmp;

	VDBG(dev, "udc_read_bytes(): %d bytes\n", bytes);

	/* dwords first */
	for (i = 0; i < bytes / UDC_DWORD_BYTES; i++) {
		*((u32 *)(buf + (i<<2))) = readl(dev->rxfifo);
	}

	/* remaining bytes must be read by byte access */
	if (bytes % UDC_DWORD_BYTES) {
		tmp = readl(dev->rxfifo);
		for (j = 0; j < bytes % UDC_DWORD_BYTES; j++) {
			*(buf + (i<<2) + j) = (u8)(tmp & UDC_BYTE_MASK);
			tmp = tmp >> UDC_BITS_PER_BYTE;
		}
	}

	return 0;
}