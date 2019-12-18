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
typedef  int UINT16 ;
struct TYPE_5__ {scalar_t__ pal; } ;
struct TYPE_8__ {TYPE_1__ m; } ;
struct TYPE_7__ {int EmuOpt; } ;
struct TYPE_6__ {int* writebuff0; int* writebuff1; scalar_t__ writebuffsel; } ;

/* Variables and functions */
 TYPE_4__ Pico ; 
 unsigned int ST_address ; 
 int addr_A1 ; 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int) ; 
 TYPE_2__* shared_ctl ; 
 int writebuff_ptr ; 

int YM2612Write_940(unsigned int a, unsigned int v, int scanline)
{
	int upd = 1;	/* the write affects sample generation */

	a &= 3;

	//printf("%05i:%03i: ym w ([%i] %02x)\n", Pico.m.frame_count, Pico.m.scanline, a, v);

	switch (a)
	{
		case 0:	/* address port 0 */
			if (addr_A1 == 0 && ST_address == v)
				return 0; /* address already selected, don't send this command to 940 */
			ST_address = v;
			addr_A1 = 0;
			/* don't send DAC or timer related address changes to 940 */
			if (v == 0x24 || v == 0x25 || v == 0x26 || v == 0x2a)
				return 0;
			upd = 0;
			break;

		case 2:	/* address port 1 */
			if (addr_A1 == 1 && ST_address == v)
				return 0;
			ST_address = v;
			addr_A1 = 1;
			upd = 0;
			break;
	}

	//printf("ym pass\n");

	if (currentConfig.EmuOpt & 4)
	{
		UINT16 *writebuff = shared_ctl->writebuffsel ? shared_ctl->writebuff0 : shared_ctl->writebuff1;

		/* detect rapid ym updates */
		if (upd && !(writebuff_ptr & 0x80000000) && scanline < 224)
		{
			int mid = Pico.m.pal ? 68 : 93;
			if (scanline > mid) {
				//printf("%05i:%03i: rapid ym\n", Pico.m.frame_count, scanline);
				writebuff[writebuff_ptr++ & 0xffff] = 0xfffe;
				writebuff_ptr |= 0x80000000;
				//printf("%05i:%03i: ym w ([%02x] %02x, upd=%i)\n", Pico.m.frame_count, scanline, addr, v, upd);
			}
		}

		/* queue this write for 940 */
		if ((writebuff_ptr&0xffff) < 2047) {
			writebuff[writebuff_ptr++ & 0xffff] = (a<<8)|v;
		} else {
			printf("warning: writebuff_ptr > 2047 ([%i] %02x)\n", a, v);
		}
	}

	return 0; // cause the engine to do updates once per frame only
}