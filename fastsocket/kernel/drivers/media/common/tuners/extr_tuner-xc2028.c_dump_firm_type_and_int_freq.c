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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 unsigned int ATI638 ; 
 unsigned int ATSC ; 
 unsigned int BASE ; 
 unsigned int CHINA ; 
 unsigned int D2620 ; 
 unsigned int D2633 ; 
 unsigned int DIBCOM52 ; 
 unsigned int DTV6 ; 
 unsigned int DTV7 ; 
 unsigned int DTV78 ; 
 unsigned int DTV8 ; 
 unsigned int F6MHZ ; 
 unsigned int F8MHZ ; 
 unsigned int FM ; 
 unsigned int HAS_IF ; 
 unsigned int IF ; 
 unsigned int INIT1 ; 
 unsigned int INPUT1 ; 
 unsigned int INPUT2 ; 
 unsigned int LCD ; 
 unsigned int LG60 ; 
 unsigned int MONO ; 
 unsigned int MTS ; 
 unsigned int NOGD ; 
 unsigned int OREN36 ; 
 unsigned int OREN538 ; 
 unsigned int QAM ; 
 unsigned int SCODE ; 
 unsigned int TOYOTA388 ; 
 unsigned int TOYOTA794 ; 
 unsigned int ZARLINK456 ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void dump_firm_type_and_int_freq(unsigned int type, u16 int_freq)
{
	 if (type & BASE)
		printk("BASE ");
	 if (type & INIT1)
		printk("INIT1 ");
	 if (type & F8MHZ)
		printk("F8MHZ ");
	 if (type & MTS)
		printk("MTS ");
	 if (type & D2620)
		printk("D2620 ");
	 if (type & D2633)
		printk("D2633 ");
	 if (type & DTV6)
		printk("DTV6 ");
	 if (type & QAM)
		printk("QAM ");
	 if (type & DTV7)
		printk("DTV7 ");
	 if (type & DTV78)
		printk("DTV78 ");
	 if (type & DTV8)
		printk("DTV8 ");
	 if (type & FM)
		printk("FM ");
	 if (type & INPUT1)
		printk("INPUT1 ");
	 if (type & LCD)
		printk("LCD ");
	 if (type & NOGD)
		printk("NOGD ");
	 if (type & MONO)
		printk("MONO ");
	 if (type & ATSC)
		printk("ATSC ");
	 if (type & IF)
		printk("IF ");
	 if (type & LG60)
		printk("LG60 ");
	 if (type & ATI638)
		printk("ATI638 ");
	 if (type & OREN538)
		printk("OREN538 ");
	 if (type & OREN36)
		printk("OREN36 ");
	 if (type & TOYOTA388)
		printk("TOYOTA388 ");
	 if (type & TOYOTA794)
		printk("TOYOTA794 ");
	 if (type & DIBCOM52)
		printk("DIBCOM52 ");
	 if (type & ZARLINK456)
		printk("ZARLINK456 ");
	 if (type & CHINA)
		printk("CHINA ");
	 if (type & F6MHZ)
		printk("F6MHZ ");
	 if (type & INPUT2)
		printk("INPUT2 ");
	 if (type & SCODE)
		printk("SCODE ");
	 if (type & HAS_IF)
		printk("HAS_IF_%d ", int_freq);
}