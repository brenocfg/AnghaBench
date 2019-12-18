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
struct fb_cmap {int len; scalar_t__ start; int /*<<< orphan*/ * transp; void* blue; void* green; void* red; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  fb_copy_cmap (int /*<<< orphan*/ ,struct fb_cmap*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (struct fb_cmap*) ; 
 int /*<<< orphan*/  fb_default_cmap (int) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

int fb_alloc_cmap(struct fb_cmap *cmap, int len, int transp)
{
    int size = len*sizeof(u16);

    if (cmap->len != len) {
	fb_dealloc_cmap(cmap);
	if (!len)
	    return 0;
	if (!(cmap->red = kmalloc(size, GFP_ATOMIC)))
	    goto fail;
	if (!(cmap->green = kmalloc(size, GFP_ATOMIC)))
	    goto fail;
	if (!(cmap->blue = kmalloc(size, GFP_ATOMIC)))
	    goto fail;
	if (transp) {
	    if (!(cmap->transp = kmalloc(size, GFP_ATOMIC)))
		goto fail;
	} else
	    cmap->transp = NULL;
    }
    cmap->start = 0;
    cmap->len = len;
    fb_copy_cmap(fb_default_cmap(len), cmap);
    return 0;

fail:
    fb_dealloc_cmap(cmap);
    return -ENOMEM;
}