#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ zbar_window_t ;
struct TYPE_13__ {int bpp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_14__ {TYPE_1__ rgb; } ;
struct TYPE_16__ {TYPE_2__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {int depth; int red_mask; int green_mask; int blue_mask; } ;
typedef  TYPE_5__ XVisualInfo ;

/* Variables and functions */
 int RGB_OFFSET (int /*<<< orphan*/ ) ; 
 int RGB_SIZE (int /*<<< orphan*/ ) ; 
 int VisualBlueMaskMask ; 
 int VisualDepthMask ; 
 int VisualGreenMaskMask ; 
 int VisualRedMaskMask ; 
 int /*<<< orphan*/  XFree (TYPE_5__*) ; 
 TYPE_5__* XGetVisualInfo (int /*<<< orphan*/ ,int,TYPE_5__*,int*) ; 
 TYPE_4__* _zbar_format_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zprintf (int,char*,int,int,int,int,int,TYPE_5__*) ; 

__attribute__((used)) static int ximage_probe_format (zbar_window_t *w,
                                uint32_t format)
{
    const zbar_format_def_t *fmt = _zbar_format_lookup(format);

    XVisualInfo visreq, *visuals = NULL;
    memset(&visreq, 0, sizeof(XVisualInfo));

    visreq.depth = fmt->p.rgb.bpp << 3;
    visreq.red_mask =
        (0xff >> RGB_SIZE(fmt->p.rgb.red)) << RGB_OFFSET(fmt->p.rgb.red);
    visreq.green_mask =
        (0xff >> RGB_SIZE(fmt->p.rgb.green)) << RGB_OFFSET(fmt->p.rgb.green);
    visreq.blue_mask =
        (0xff >> RGB_SIZE(fmt->p.rgb.blue)) << RGB_OFFSET(fmt->p.rgb.blue);

    int n;
    visuals = XGetVisualInfo(w->display,
                             VisualDepthMask | VisualRedMaskMask |
                             VisualGreenMaskMask | VisualBlueMaskMask,
                             &visreq, &n);

    zprintf(8, "bits=%d r=%08lx g=%08lx b=%08lx: n=%d visuals=%p\n",
            visreq.depth, visreq.red_mask, visreq.green_mask,
            visreq.blue_mask, n, visuals);
    if(!visuals)
        return(1);
    XFree(visuals);
    if(!n)
        return(-1);

    return(0);
}