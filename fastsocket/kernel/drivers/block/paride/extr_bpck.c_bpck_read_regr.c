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
 int* cont_map ; 
 int /*<<< orphan*/  e2 () ; 
 int j44 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int r4 () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int bpck_read_regr( PIA *pi, int cont, int regr )

{       int r, l, h;

	r = regr + cont_map[cont];

	switch (pi->mode) {

	case 0: w0(r & 0xf); w0(r); t2(2); t2(4);
	        l = r1();
        	t2(4);
        	h = r1();
        	return j44(l,h);

	case 1: w0(r & 0xf); w0(r); t2(2);
	        e2(); t2(0x20);
		t2(4); h = r0();
	        t2(1); t2(0x20);
	        return h;

	case 2:
	case 3:
	case 4: w0(r); w2(9); w2(0); w2(0x20);
		h = r4();
		w2(0);
		return h;

	}
	return -1;
}