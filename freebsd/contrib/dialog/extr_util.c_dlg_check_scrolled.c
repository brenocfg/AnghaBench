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
#define  DLGK_GRID_DOWN 133 
#define  DLGK_GRID_UP 132 
#define  DLGK_PAGE_FIRST 131 
#define  DLGK_PAGE_LAST 130 
#define  DLGK_PAGE_NEXT 129 
#define  DLGK_PAGE_PREV 128 
 int FALSE ; 
 int TRUE ; 

int
dlg_check_scrolled(int key, int last, int page, bool * show, int *offset)
{
    int code = 0;

    *show = FALSE;

    switch (key) {
    case DLGK_PAGE_FIRST:
	if (*offset > 0) {
	    *offset = 0;
	    *show = TRUE;
	}
	break;
    case DLGK_PAGE_LAST:
	if (*offset < last) {
	    *offset = last;
	    *show = TRUE;
	}
	break;
    case DLGK_GRID_UP:
	if (*offset > 0) {
	    --(*offset);
	    *show = TRUE;
	}
	break;
    case DLGK_GRID_DOWN:
	if (*offset < last) {
	    ++(*offset);
	    *show = TRUE;
	}
	break;
    case DLGK_PAGE_PREV:
	if (*offset > 0) {
	    *offset -= page;
	    if (*offset < 0)
		*offset = 0;
	    *show = TRUE;
	}
	break;
    case DLGK_PAGE_NEXT:
	if (*offset < last) {
	    *offset += page;
	    if (*offset > last)
		*offset = last;
	    *show = TRUE;
	}
	break;
    default:
	code = -1;
	break;
    }
    return code;
}