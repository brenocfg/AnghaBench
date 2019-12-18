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
 int /*<<< orphan*/  ERR ; 
 scalar_t__ have_last_getc ; 
 int /*<<< orphan*/  last_getc ; 
 scalar_t__ used_last_getc ; 

void
dlg_flush_getc(void)
{
    last_getc = ERR;
#ifdef USE_WIDE_CURSES
    have_last_getc = 0;
    used_last_getc = 0;
#endif
}