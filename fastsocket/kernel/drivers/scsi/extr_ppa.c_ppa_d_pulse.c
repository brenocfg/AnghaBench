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

/* Variables and functions */
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,unsigned char) ; 

__attribute__((used)) static inline void ppa_d_pulse(unsigned short ppb, unsigned char b)
{
	w_dtr(ppb, b);
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0xe);
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0x4);
	w_ctr(ppb, 0xc);
}