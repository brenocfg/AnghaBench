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
 int ERR ; 
 int last_getc ; 
 int used_last_getc ; 

int
dlg_last_getc(void)
{
#ifdef USE_WIDE_CURSES
    if (used_last_getc != 1)
	return ERR;		/* not really an error... */
#endif
    return last_getc;
}