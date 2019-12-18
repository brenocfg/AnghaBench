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
 int CORGI_GPIO_ALL_STROBE_BIT ; 
 int CORGI_GPIO_STROBE_BIT (int) ; 
 int GPCR2 ; 
 int GPDR2 ; 

__attribute__((used)) static inline void corgikbd_reset_col(int col)
{
	/* STROBE col -> Low */
	GPCR2 = CORGI_GPIO_STROBE_BIT(col);
	/* STROBE col -> out, not col -> HiZ */
	GPDR2 = (GPDR2 & ~CORGI_GPIO_ALL_STROBE_BIT) | CORGI_GPIO_STROBE_BIT(col);
}