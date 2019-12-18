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
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 
 int /*<<< orphan*/  w4 (char) ; 
 int /*<<< orphan*/  w4l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w4w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void epat_write_block( PIA *pi, char * buf, int count )   

{	int ph, k;

	switch (pi->mode) {

	case 0:
	case 1:
	case 2: w0(0x67); w2(1); w2(5);
		ph = 0;
		for(k=0;k<count;k++) {
		  	w0(buf[k]);
			w2(4+ph);
			ph = 1 - ph;
		}
		w2(7); w2(4);
		break;

	case 3: w3(0xc0); 
		for(k=0;k<count;k++) w4(buf[k]);
		w2(4);
		break;

	case 4: w3(0xc0); 
		for(k=0;k<(count/2);k++) w4w(((u16 *)buf)[k]);
		w2(4);
		break;

	case 5: w3(0xc0); 
		for(k=0;k<(count/4);k++) w4l(((u32 *)buf)[k]);
		w2(4);
		break;

	}
}