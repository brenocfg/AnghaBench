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
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 char j44 (int,int) ; 
 int /*<<< orphan*/  op (int) ; 
 char r0 () ; 
 int r1 () ; 
 int /*<<< orphan*/  vl (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void on20_read_block( PIA *pi, char * buf, int count )

{	int     k, l, h; 

	op(1); vl(1); op(0);

	for (k=0;k<count;k++) 
	    if (pi->mode) {
		w2(4); w2(0x26); buf[k] = r0();
	    } else {
		w2(6); l = r1(); w2(4);
		w2(6); h = r1(); w2(4);
		buf[k] = j44(l,h);
	    }
	w2(4);
}