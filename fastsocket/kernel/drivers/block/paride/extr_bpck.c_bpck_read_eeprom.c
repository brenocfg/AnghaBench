#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; int delay; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int RR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR (int,int) ; 
 int /*<<< orphan*/  bpck_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  bpck_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  bpck_force_spp (TYPE_1__*) ; 

__attribute__((used)) static void bpck_read_eeprom ( PIA *pi, char * buf )

{       int i,j,k,n,p,v,f, om, od;

	bpck_force_spp(pi);

	om = pi->mode;  od = pi->delay;
	pi->mode = 0; pi->delay = 6;

	bpck_connect(pi);
	
	n = 0;
	WR(4,0);
	for (i=0;i<64;i++) {
	    WR(6,8);  
	    WR(6,0xc);
	    p = 0x100;
	    for (k=0;k<9;k++) {
		f = (((i + 0x180) & p) != 0) * 2;
		WR(6,f+0xc); 
		WR(6,f+0xd); 
		WR(6,f+0xc);
		p = (p >> 1);
	    }
	    for (j=0;j<2;j++) {
		v = 0;
		for (k=0;k<8;k++) {
		    WR(6,0xc); 
		    WR(6,0xd); 
		    WR(6,0xc); 
		    f = RR(0);
		    v = 2*v + (f == 0x84);
		}
		buf[2*i+1-j] = v;
	    }
	}
	WR(6,8);
	WR(6,0);
	WR(5,8);

	bpck_disconnect(pi);

        if (om >= 2) {
                bpck_connect(pi);
                WR(7,3);
                WR(4,8);
                bpck_disconnect(pi);
        }

	pi->mode = om; pi->delay = od;
}