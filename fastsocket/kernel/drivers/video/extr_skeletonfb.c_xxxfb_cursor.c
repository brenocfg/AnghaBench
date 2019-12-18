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
struct fb_info {int dummy; } ;
struct fb_cursor {int dummy; } ;

/* Variables and functions */

int xxxfb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
/*
 *      @set: 	Which fields we are altering in struct fb_cursor 
 *	@enable: Disable or enable the cursor 
 *      @rop: 	The bit operation we want to do. 
 *      @mask:  This is the cursor mask bitmap. 
 *      @dest:  A image of the area we are going to display the cursor.
 *		Used internally by the driver.	 
 *      @hot:	The hot spot. 
 *	@image:	The actual data for the cursor image.
 *
 *      NOTES ON FLAGS (cursor->set):
 *
 *      FB_CUR_SETIMAGE - the cursor image has changed (cursor->image.data)
 *      FB_CUR_SETPOS   - the cursor position has changed (cursor->image.dx|dy)
 *      FB_CUR_SETHOT   - the cursor hot spot has changed (cursor->hot.dx|dy)
 *      FB_CUR_SETCMAP  - the cursor colors has changed (cursor->fg_color|bg_color)
 *      FB_CUR_SETSHAPE - the cursor bitmask has changed (cursor->mask)
 *      FB_CUR_SETSIZE  - the cursor size has changed (cursor->width|height)
 *      FB_CUR_SETALL   - everything has changed
 *
 *      NOTES ON ROPs (cursor->rop, Raster Operation)
 *
 *      ROP_XOR         - cursor->image.data XOR cursor->mask
 *      ROP_COPY        - curosr->image.data AND cursor->mask
 *
 *      OTHER NOTES:
 *
 *      - fbcon only supports a 2-color cursor (cursor->image.depth = 1)
 *      - The fb_cursor structure, @cursor, _will_ always contain valid
 *        fields, whether any particular bitfields in cursor->set is set
 *        or not.
 */
}