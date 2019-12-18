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
 int GPLR0 ; 
 int GPLR1 ; 
 int GPLR2 ; 

__attribute__((used)) static inline int spitzkbd_get_row_status(int col)
{
	return ((GPLR0 >> 12) & 0x01) | ((GPLR0 >> 16) & 0x02)
		| ((GPLR2 >> 25) & 0x04) | ((GPLR1 << 1) & 0x08)
		| ((GPLR1 >> 0) & 0x10) | ((GPLR1 >> 1) & 0x60);
}