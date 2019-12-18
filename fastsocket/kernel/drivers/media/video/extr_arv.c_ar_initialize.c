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
struct video_device {int dummy; } ;
struct ar_device {scalar_t__ size; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARINTSEL ; 
 unsigned long ARINTSEL_INT3 ; 
 int /*<<< orphan*/  ARVCR0 ; 
 unsigned long ARVCR0_RST ; 
 int ARVCR0_VDS ; 
 int /*<<< orphan*/  ARVCR1 ; 
 unsigned long ARVCR1_NORMAL ; 
 unsigned long ARVCR1_QVGA ; 
 scalar_t__ AR_MODE_NORMAL ; 
 scalar_t__ AR_SIZE_QVGA ; 
 int /*<<< orphan*/  DEBUG (int,char*) ; 
 int ENODEV ; 
 int ar_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  iic (int,int,int,int,int) ; 
 int /*<<< orphan*/  init_iic () ; 
 int /*<<< orphan*/  printk (char*) ; 
 struct ar_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int ar_initialize(struct video_device *dev)
{
	struct ar_device *ar = video_get_drvdata(dev);
	unsigned long cr = 0;
	int i,found=0;

	DEBUG(1, "ar_initialize:\n");

	/*
	 * initialize AR LSI
	 */
	ar_outl(0, ARVCR0);		/* assert reset of AR LSI */
	for (i = 0; i < 0x18; i++)	/* wait for over 10 cycles @ 27MHz */
		cpu_relax();
	ar_outl(ARVCR0_RST, ARVCR0);	/* negate reset of AR LSI (enable) */
	for (i = 0; i < 0x40d; i++)	/* wait for over 420 cycles @ 27MHz */
		cpu_relax();

	/* AR uses INT3 of CPU as interrupt pin. */
	ar_outl(ARINTSEL_INT3, ARINTSEL);

	if (ar->size == AR_SIZE_QVGA)
		cr |= ARVCR1_QVGA;
	if (ar->mode == AR_MODE_NORMAL)
		cr |= ARVCR1_NORMAL;
	ar_outl(cr, ARVCR1);

	/*
	 * Initialize IIC so that CPU can communicate with AR LSI,
	 * and send boot commands to AR LSI.
	 */
	init_iic();

	for (i = 0; i < 0x100000; i++) {	/* > 0xa1d10,  56ms */
		if ((ar_inl(ARVCR0) & ARVCR0_VDS)) {	/* VSYNC */
			found = 1;
			break;
		}
	}

	if (found == 0)
		return -ENODEV;

	printk("arv: Initializing ");

	iic(2,0x78,0x11,0x01,0x00);	/* start */
	iic(3,0x78,0x12,0x00,0x06);
	iic(3,0x78,0x12,0x12,0x30);
	iic(3,0x78,0x12,0x15,0x58);
	iic(3,0x78,0x12,0x17,0x30);
	printk(".");
	iic(3,0x78,0x12,0x1a,0x97);
	iic(3,0x78,0x12,0x1b,0xff);
	iic(3,0x78,0x12,0x1c,0xff);
	iic(3,0x78,0x12,0x26,0x10);
	iic(3,0x78,0x12,0x27,0x00);
	printk(".");
	iic(2,0x78,0x34,0x02,0x00);
	iic(2,0x78,0x7a,0x10,0x00);
	iic(2,0x78,0x80,0x39,0x00);
	iic(2,0x78,0x81,0xe6,0x00);
	iic(2,0x78,0x8d,0x00,0x00);
	printk(".");
	iic(2,0x78,0x8e,0x0c,0x00);
	iic(2,0x78,0x8f,0x00,0x00);
#if 0
	iic(2,0x78,0x90,0x00,0x00);	/* AWB on=1 off=0 */
#endif
	iic(2,0x78,0x93,0x01,0x00);
	iic(2,0x78,0x94,0xcd,0x00);
	iic(2,0x78,0x95,0x00,0x00);
	printk(".");
	iic(2,0x78,0x96,0xa0,0x00);
	iic(2,0x78,0x97,0x00,0x00);
	iic(2,0x78,0x98,0x60,0x00);
	iic(2,0x78,0x99,0x01,0x00);
	iic(2,0x78,0x9a,0x19,0x00);
	printk(".");
	iic(2,0x78,0x9b,0x02,0x00);
	iic(2,0x78,0x9c,0xe8,0x00);
	iic(2,0x78,0x9d,0x02,0x00);
	iic(2,0x78,0x9e,0x2e,0x00);
	iic(2,0x78,0xb8,0x78,0x00);
	iic(2,0x78,0xba,0x05,0x00);
#if 0
	iic(2,0x78,0x83,0x8c,0x00);	/* brightness */
#endif
	printk(".");

	/* color correction */
	iic(3,0x78,0x49,0x00,0x95);	/* a		*/
	iic(3,0x78,0x49,0x01,0x96);	/* b		*/
	iic(3,0x78,0x49,0x03,0x85);	/* c		*/
	iic(3,0x78,0x49,0x04,0x97);	/* d		*/
	iic(3,0x78,0x49,0x02,0x7e);	/* e(Lo)	*/
	iic(3,0x78,0x49,0x05,0xa4);	/* f(Lo)	*/
	iic(3,0x78,0x49,0x06,0x04);	/* e(Hi)	*/
	iic(3,0x78,0x49,0x07,0x04);	/* e(Hi)	*/
	iic(2,0x78,0x48,0x01,0x00);	/* on=1 off=0	*/

	printk(".");
	iic(2,0x78,0x11,0x00,0x00);	/* end */
	printk(" done\n");
	return 0;
}