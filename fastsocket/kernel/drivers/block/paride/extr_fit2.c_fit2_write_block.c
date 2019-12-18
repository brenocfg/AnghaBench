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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void fit2_write_block( PIA *pi, char * buf, int count )

{	int k;


	w2(0xc); w0(0); 
	for (k=0;k<count/2;k++) {
		w2(4); w0(buf[2*k]); 
		w2(5); w0(buf[2*k+1]);
	}
	w2(4);
}