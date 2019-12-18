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
 int cubic_interpolate_pixel (int,int,int,int) ; 

__attribute__((used)) static void cubic_interpolate_line(
        uint8_t *dst,
        uint8_t *cur,
        int width,
        int height,
        int stride,
        int y)
{
    int w = width;
    int x;

    for( x = 0; x < w; x++)
    {
        int a, b, c, d;
        a = b = c = d = 0;

        if( y >= 3 )
        {
            /* Normal top*/
            a = cur[-3*stride];
            b = cur[-stride];
        }
        else if( y == 2 || y == 1 )
        {
            /* There's only one sample above this pixel, use it twice. */
            a = cur[-stride];
            b = cur[-stride];
        }
        else if( y == 0 )
        {
            /* No samples above, triple up on the one below. */
            a = cur[+stride];
            b = cur[+stride];
        }

        if( y <= ( height - 4 ) )
        {
            /* Normal bottom*/
            c = cur[+stride];
            d = cur[3*stride];
        }
        else if( y == ( height - 3 ) || y == ( height - 2 ) )
        {
            /* There's only one sample below, use it twice. */
            c = cur[+stride];
            d = cur[+stride];
        }
        else if( y == height - 1)
        {
            /* No samples below, triple up on the one above. */
            c = cur[-stride];
            d = cur[-stride];
        }

        dst[0] = cubic_interpolate_pixel( a, b, c, d );

        dst++;
        cur++;
    }
}