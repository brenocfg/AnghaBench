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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static void pkcs12_fill_buffer( unsigned char *data, size_t data_len,
                                const unsigned char *filler, size_t fill_len )
{
    unsigned char *p = data;
    size_t use_len;

    while( data_len > 0 )
    {
        use_len = ( data_len > fill_len ) ? fill_len : data_len;
        memcpy( p, filler, use_len );
        p += use_len;
        data_len -= use_len;
    }
}