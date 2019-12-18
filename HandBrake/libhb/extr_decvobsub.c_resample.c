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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void resample( uint8_t * dst, uint8_t * src, int dst_w, int src_w )
{
    int dst_x, src_x, err, cnt, sum, val;

    if( dst_w < src_w )
    {
        // sample down
        sum = 0;
        val = 0;
        cnt = 0;
        err = src_w / 2;
        dst_x = 0;
        for( src_x = 0; src_x < src_w; src_x++ )
        {
            sum += src[src_x];
            cnt++;
            err -= dst_w;
            if( err < 0 )
            {
                val = sum / cnt;
                dst[dst_x++] = val;
                sum = cnt = 0;
                err += src_w;
            }
        }
        for( ; dst_x < dst_w; dst_x++ )
        {
            dst[dst_x] = val;
        }
    }
    else
    {
        // sample up
        err = dst_w / 2;
        src_x = 0;
        for( dst_x = 0; dst_x < dst_w; dst_x++ )
        {
            dst[dst_x] = src[src_x];
            err -= src_w;
            if( err < 0 )
            {
                src_x++;
                err += dst_w;
            }
        }
    }
}