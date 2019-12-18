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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* plane; } ;
typedef  TYPE_2__ hb_buffer_t ;
struct TYPE_4__ {int stride; int height; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DARK ; 
 int absdiff (int,scalar_t__) ; 
 scalar_t__ clampBlack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int column_all_dark( hb_buffer_t* buf, int top, int bottom, int col )
{
    int stride = buf->plane[0].stride;
    int height = buf->plane[0].height - top - bottom;
    uint8_t *luma = buf->plane[0].data + stride * top + col;

    // compute the average value of the column
    int i = height, avg = 0, row = 0;
    for ( ; --i >= 0; row += stride )
    {
        avg += clampBlack( luma[row] );
    }
    avg /= height;
    if ( avg >= DARK )
        return 0;

    // since we're trying to detect smooth borders, only take the column if
    // all pixels are within +-16 of the average.
    i = height, row = 0;
    for ( ; --i >= 0; row += stride )
    {
        if ( absdiff( avg, clampBlack( luma[row] ) ) > 16 )
            return 0;
    }
    return 1;
}