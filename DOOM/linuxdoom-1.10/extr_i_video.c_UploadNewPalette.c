#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
typedef  int boolean ;
struct TYPE_5__ {scalar_t__ c_class; int depth; scalar_t__ class; } ;
struct TYPE_4__ {int pixel; int flags; int red; int green; int blue; } ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int DoBlue ; 
 int DoGreen ; 
 int DoRed ; 
 scalar_t__ PseudoColor ; 
 int /*<<< orphan*/  XStoreColors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  X_display ; 
 TYPE_2__ X_visualinfo ; 
 TYPE_1__* colors ; 
 int** gammatable ; 
 size_t usegamma ; 

void UploadNewPalette(Colormap cmap, byte *palette)
{

    register int	i;
    register int	c;
    static boolean	firstcall = true;

#ifdef __cplusplus
    if (X_visualinfo.c_class == PseudoColor && X_visualinfo.depth == 8)
#else
    if (X_visualinfo.class == PseudoColor && X_visualinfo.depth == 8)
#endif
	{
	    // initialize the colormap
	    if (firstcall)
	    {
		firstcall = false;
		for (i=0 ; i<256 ; i++)
		{
		    colors[i].pixel = i;
		    colors[i].flags = DoRed|DoGreen|DoBlue;
		}
	    }

	    // set the X colormap entries
	    for (i=0 ; i<256 ; i++)
	    {
		c = gammatable[usegamma][*palette++];
		colors[i].red = (c<<8) + c;
		c = gammatable[usegamma][*palette++];
		colors[i].green = (c<<8) + c;
		c = gammatable[usegamma][*palette++];
		colors[i].blue = (c<<8) + c;
	    }

	    // store the colors to the current colormap
	    XStoreColors(X_display, cmap, colors, 256);

	}
}