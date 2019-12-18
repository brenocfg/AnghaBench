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
 int* malloc (int) ; 

__attribute__((used)) static void CreateDecodedNAL( uint8_t **dst, int *dst_len,
                              const uint8_t *src, int src_len )
{
    const uint8_t *end = &src[src_len];
    uint8_t *d = malloc( src_len );

    *dst = d;

    if( d )
    {
        while( src < end )
        {
            if( src < end - 3 && src[0] == 0x00 && src[1] == 0x00 &&
                src[2] == 0x01 )
            {
                // Next start code found
                break;
            }
            if( src < end - 3 && src[0] == 0x00 && src[1] == 0x00 &&
                src[2] == 0x03 )
            {
                *d++ = 0x00;
                *d++ = 0x00;

                src += 3;
                continue;
            }
            *d++ = *src++;
        }
    }
    *dst_len = d - *dst;
}