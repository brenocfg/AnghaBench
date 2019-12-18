#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 char j44 (int,int) ; 
 char j53 (int,int) ; 
 char r0 () ; 
 int r1 () ; 
 int r2 () ; 
 char r4 () ; 
 int /*<<< orphan*/  r4l () ; 
 int /*<<< orphan*/  r4w () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 

__attribute__((used)) static void epat_read_block( PIA *pi, char * buf, int count )

{	int  k, ph, a, b;

	switch (pi->mode) {

	case 0:	w0(7); w2(1); w2(3); w0(0xff);
		ph = 0;
		for(k=0;k<count;k++) {
			if (k == count-1) w0(0xfd);
			w2(6+ph); a = r1();
			if (a & 8) b = a; 
			  else { w2(4+ph); b = r1(); }
			buf[k] = j44(a,b);
			ph =  1 - ph;
		}
		w0(0); w2(4);
		break;

	case 1: w0(0x47); w2(1); w2(5); w0(0xff);
		ph = 0;
		for(k=0;k<count;k++) {
			if (k == count-1) w0(0xfd); 
			w2(4+ph);
			a = r1(); b = r2();
			buf[k] = j53(a,b);
			ph = 1 - ph;
		}
		w0(0); w2(4);
		break;

	case 2: w0(0x27); w2(1); w2(0x25); w0(0);
		ph = 0;
		for(k=0;k<count-1;k++) {
			w2(0x24+ph);
			buf[k] = r0();
			ph = 1 - ph;
		}
		w2(0x26); w2(0x27); buf[count-1] = r0(); 
		w2(0x25); w2(4);
		break;

	case 3: w3(0x80); w2(0x24);
		for(k=0;k<count-1;k++) buf[k] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		break;

	case 4: w3(0x80); w2(0x24);
		for(k=0;k<(count/2)-1;k++) ((u16 *)buf)[k] = r4w();
		buf[count-2] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		break;

	case 5: w3(0x80); w2(0x24);
		for(k=0;k<(count/4)-1;k++) ((u32 *)buf)[k] = r4l();
		for(k=count-4;k<count-1;k++) buf[k] = r4();
		w2(4); w3(0xa0); w2(0x24); buf[count-1] = r4();
		w2(4);
		break;

	}
}