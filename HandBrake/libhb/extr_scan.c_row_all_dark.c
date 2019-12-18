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
struct TYPE_4__ {int width; int stride; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DARK ; 
 int absdiff (int,scalar_t__) ; 
 scalar_t__ clampBlack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int row_all_dark( hb_buffer_t* buf, int row )
{
    int width = buf->plane[0].width;
    int stride = buf->plane[0].stride;
    uint8_t *luma = buf->plane[0].data + stride * row;

    // compute the average luma value of the row
    int i, avg = 0;
    for ( i = 0; i < width; ++i )
    {
        avg += clampBlack( luma[i] );
    }
    avg /= width;
    if ( avg >= DARK )
        return 0;

    // since we're trying to detect smooth borders, only take the row if
    // all pixels are within +-16 of the average (this range is fairly coarse
    // but there's a lot of quantization noise for luma values near black
    // so anything less will fail to crop because of the noise).
    for ( i = 0; i < width; ++i )
    {
        if ( absdiff( avg, clampBlack( luma[i] ) ) > 16 )
            return 0;
    }
    return 1;
}