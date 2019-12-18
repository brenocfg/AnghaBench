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
typedef  int /*<<< orphan*/  u32 ;
struct udc {int /*<<< orphan*/  rxfifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct udc*,char*,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udc_rxfifo_read_dwords(struct udc *dev, u32 *buf, int dwords)
{
	int i;

	VDBG(dev, "udc_read_dwords(): %d dwords\n", dwords);

	for (i = 0; i < dwords; i++) {
		*(buf + i) = readl(dev->rxfifo);
	}
	return 0;
}