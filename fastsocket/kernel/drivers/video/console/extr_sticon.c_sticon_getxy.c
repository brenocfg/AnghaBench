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
struct vc_data {unsigned long vc_origin; unsigned long vc_scr_end; unsigned long vc_cols; scalar_t__ vc_num; } ;

/* Variables and functions */
 scalar_t__ fg_console ; 
 unsigned long softback_buf ; 
 unsigned long softback_curr ; 
 unsigned long softback_end ; 
 unsigned long softback_in ; 
 scalar_t__ softback_lines ; 

__attribute__((used)) static unsigned long sticon_getxy(struct vc_data *conp, unsigned long pos,
				  int *px, int *py)
{
    int x, y;
    unsigned long ret;
    if (pos >= conp->vc_origin && pos < conp->vc_scr_end) {
    	unsigned long offset = (pos - conp->vc_origin) / 2;
    	
    	x = offset % conp->vc_cols;
    	y = offset / conp->vc_cols;
    	if (conp->vc_num == fg_console)
    	    y += softback_lines;
    	ret = pos + (conp->vc_cols - x) * 2;
    } else if (conp->vc_num == fg_console && softback_lines) {
    	unsigned long offset = pos - softback_curr;
    	
    	if (pos < softback_curr)
    	    offset += softback_end - softback_buf;
    	offset /= 2;
    	x = offset % conp->vc_cols;
    	y = offset / conp->vc_cols;
	ret = pos + (conp->vc_cols - x) * 2;
	if (ret == softback_end)
	    ret = softback_buf;
	if (ret == softback_in)
	    ret = conp->vc_origin;
    } else {
    	/* Should not happen */
    	x = y = 0;
    	ret = conp->vc_origin;
    }
    if (px) *px = x;
    if (py) *py = y;
    return ret;
}