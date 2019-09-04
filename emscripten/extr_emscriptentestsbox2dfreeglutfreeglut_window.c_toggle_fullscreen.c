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
 int ewmh_fullscr_toggle () ; 
 int resize_fullscr_toogle () ; 

__attribute__((used)) static int toggle_fullscreen(void)
{
    /* first try the EWMH (_NET_WM_STATE) method ... */
    if(ewmh_fullscr_toggle() != -1) {
        return 0;
    }

    /* fall back to resizing the window */
    if(resize_fullscr_toogle() != -1) {
        return 0;
    }
    return -1;
}