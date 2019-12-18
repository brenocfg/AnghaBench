#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int v_depth; unsigned int v_width; unsigned int v_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_blit_rect_16 (int,int,int,int,int,int,int,unsigned char const*,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  vc_blit_rect_30 (int,int,int,int,int,int,int,unsigned char const*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  vc_blit_rect_32 (int,int,int,int,int,int,int,unsigned char const*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  vc_blit_rect_8 (int,int,int,int,int,int,int,unsigned char const*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  vc_clut ; 
 int /*<<< orphan*/  vc_clut8 ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void vc_blit_rect(int x, int y, int bx,
			    int width, int height,
			    int sourceRow, int backRow,
			    const unsigned char * dataPtr,
			    void * backBuffer,
			    unsigned int flags)
{
    if (!vinfo.v_depth)                                return;
    if (((unsigned int)(x + width))  > vinfo.v_width)  return;
    if (((unsigned int)(y + height)) > vinfo.v_height) return;

    switch( vinfo.v_depth) {
	case 8:
            if( vc_clut8 == vc_clut)
                vc_blit_rect_8( x, y, bx, width, height, sourceRow, backRow, dataPtr, (unsigned char *) backBuffer, flags );
	    break;
	case 16:
	    vc_blit_rect_16( x, y, bx, width, height, sourceRow, backRow, dataPtr, (unsigned short *) backBuffer, flags );
	    break;
	case 32:
	    vc_blit_rect_32( x, y, bx, width, height, sourceRow, backRow, dataPtr, (unsigned int *) backBuffer, flags );
	    break;
	case 30:
	    vc_blit_rect_30( x, y, bx, width, height, sourceRow, backRow, dataPtr, (unsigned int *) backBuffer, flags );
	    break;
    }
}