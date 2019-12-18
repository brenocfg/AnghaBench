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
struct vc_data {scalar_t__ vc_num; int vc_size_row; scalar_t__ vc_origin; } ;

/* Variables and functions */
 scalar_t__ fg_console ; 
 unsigned long softback_buf ; 
 int softback_curr ; 
 unsigned long softback_end ; 
 int softback_lines ; 

__attribute__((used)) static u16 *sticon_screen_pos(struct vc_data *conp, int offset)
{
    int line;
    unsigned long p;

    if (conp->vc_num != fg_console || !softback_lines)
    	return (u16 *)(conp->vc_origin + offset);
    line = offset / conp->vc_size_row;
    if (line >= softback_lines)
    	return (u16 *)(conp->vc_origin + offset - softback_lines * conp->vc_size_row);
    p = softback_curr + offset;
    if (p >= softback_end)
    	p += softback_buf - softback_end;
    return (u16 *)p;
}