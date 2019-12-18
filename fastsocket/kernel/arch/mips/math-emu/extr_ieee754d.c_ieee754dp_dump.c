#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bits; } ;
typedef  TYPE_1__ ieee754dp ;

/* Variables and functions */
 scalar_t__ DPBEXP (TYPE_1__) ; 
 int DPMANT (TYPE_1__) ; 
 int /*<<< orphan*/  DPSIGN (TYPE_1__) ; 
 scalar_t__ DP_EBIAS ; 
 int /*<<< orphan*/  DP_FBITS ; 
 int DP_MBIT (int) ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int ieee754dp_class (TYPE_1__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

ieee754dp ieee754dp_dump(char *m, ieee754dp x)
{
	int i;

	printk("%s", m);
	printk("<%08x,%08x>\n", (unsigned) (x.bits >> 32),
	       (unsigned) x.bits);
	printk("\t=");
	switch (ieee754dp_class(x)) {
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_SNAN:
		printk("Nan %c", DPSIGN(x) ? '-' : '+');
		for (i = DP_FBITS - 1; i >= 0; i--)
			printk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		break;
	case IEEE754_CLASS_INF:
		printk("%cInfinity", DPSIGN(x) ? '-' : '+');
		break;
	case IEEE754_CLASS_ZERO:
		printk("%cZero", DPSIGN(x) ? '-' : '+');
		break;
	case IEEE754_CLASS_DNORM:
		printk("%c0.", DPSIGN(x) ? '-' : '+');
		for (i = DP_FBITS - 1; i >= 0; i--)
			printk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		printk("e%d", DPBEXP(x) - DP_EBIAS);
		break;
	case IEEE754_CLASS_NORM:
		printk("%c1.", DPSIGN(x) ? '-' : '+');
		for (i = DP_FBITS - 1; i >= 0; i--)
			printk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		printk("e%d", DPBEXP(x) - DP_EBIAS);
		break;
	default:
		printk("Illegal/Unknown IEEE754 value class");
	}
	printk("\n");
	return x;
}