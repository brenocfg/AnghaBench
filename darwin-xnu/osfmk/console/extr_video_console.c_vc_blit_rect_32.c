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
struct TYPE_2__ {int v_rowbytes; scalar_t__ v_baseaddr; } ;

/* Variables and functions */
 unsigned int kDataAlpha ; 
 unsigned int kDataBack ; 
 unsigned int kDataIndexed ; 
 unsigned int kDataRotate ; 
 unsigned int kSave ; 
 int* vc_clut ; 
 scalar_t__ vc_progress_white ; 
 int*** vc_rotate_matr ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void vc_blit_rect_32(int x, int y, int bx, 
                            int width, int height,
			    int sourceRow, int backRow,
			    const unsigned char * dataPtr,
			    unsigned int * backPtr,
			    unsigned int flags)
{
    volatile unsigned int * dst;
    int line, col;
    unsigned int data = 0, out = 0, back = 0;
    int sx, sy, a, b, c, d;
    int scale = 0x10000;

    a = vc_rotate_matr[kDataRotate & flags][0][0] * scale;
    b = vc_rotate_matr[kDataRotate & flags][0][1] * scale;
    c = vc_rotate_matr[kDataRotate & flags][1][0] * scale;
    d = vc_rotate_matr[kDataRotate & flags][1][1] * scale;
    sx = ((a + b) < 0) ? ((width * scale)  - 0x8000) : 0;
    sy = ((c + d) < 0) ? ((height * scale) - 0x8000) : 0;

    if (!sourceRow) data = (unsigned int)(uintptr_t)dataPtr;
    else if (1 == sourceRow) a = 0;
        
    if (backPtr)
	backPtr += bx;
    dst = (volatile unsigned int *) (vinfo.v_baseaddr +
                                    (y * vinfo.v_rowbytes) +
                                    (x * 4));

    for( line = 0; line < height; line++)
    {
        for( col = 0; col < width; col++)
	{
	    if (sourceRow) data = dataPtr[((sx + (col * a) + (line * b)) >> 16)
				+ sourceRow * (((sy + (col * c) + (line * d)) >> 16))];
	    if (backPtr) {
		if (kSave & flags) {
		    back = *(dst + col);
		    *backPtr++ = back;
		} else
		    back = *backPtr++;
	    }
	    if (kDataIndexed & flags) {
		out =     (vc_clut[data*3 + 0] << 16)
			| (vc_clut[data*3 + 1] << 8)
			| (vc_clut[data*3 + 2]);
	    } else if (kDataAlpha & flags) {
		out = (((((back & 0x00ff00ff) * data) + 0x00ff00ff) >> 8) & 0x00ff00ff)
		     | (((((back & 0x0000ff00) * data) + 0x0000ff00) >> 8) & 0x0000ff00);
		if (vc_progress_white) out += ((0xff - data) << 16)
					    | ((0xff - data) << 8)
					    |  (0xff - data);
            } else if (kDataBack & flags)
		out = back;
	    else
		out = data;
            *(dst + col) = out;
	}
        dst = (volatile unsigned int *) (((volatile char*)dst) + vinfo.v_rowbytes);
	if (backPtr)
	    backPtr += backRow - width;
    }
}