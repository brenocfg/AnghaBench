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
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 char j44 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 char r4 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void fit3_read_block( PIA *pi, char * buf, int count )

{	int  k, a, b, c, d;

	switch (pi->mode) {

	case 0: w2(0xc); w0(0x10); w2(0x8); w2(0xc);
		for (k=0;k<count/2;k++) {
		    w2(0xd); a = r1();
		    w2(0xf); b = r1();
		    w2(0xc); c = r1();
		    w2(0xe); d = r1();
		    buf[2*k  ] = j44(a,b);
		    buf[2*k+1] = j44(c,d);
		}
		w2(0xc);
		break;

	case 1: w2(0xc); w0(0x90); w2(0x8); w2(0xc); 
		w2(0xec); w2(0xee);
		for (k=0;k<count/2;k++) {
		    w2(0xef); a = r0();
		    w2(0xee); b = r0();
                    buf[2*k  ] = a;
                    buf[2*k+1] = b;
		}
		w2(0xec); 
		w2(0xc);
		break;

	case 2: w2(0xc); w0(0x90); w2(0x8); w2(0xc); 
                w2(0xec);
		for (k=0;k<count;k++) buf[k] = r4();
                w2(0xc);
		break;

	}
}