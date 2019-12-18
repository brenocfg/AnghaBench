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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_des_setkey (int /*<<< orphan*/ *,unsigned char const*) ; 

__attribute__((used)) static void des3_set3key( uint32_t esk[96],
                          uint32_t dsk[96],
                          const unsigned char key[24] )
{
    int i;

    mbedtls_des_setkey( esk, key );
    mbedtls_des_setkey( dsk + 32, key +  8 );
    mbedtls_des_setkey( esk + 64, key + 16 );

    for( i = 0; i < 32; i += 2 )
    {
        dsk[i     ] = esk[94 - i];
        dsk[i +  1] = esk[95 - i];

        esk[i + 32] = dsk[62 - i];
        esk[i + 33] = dsk[63 - i];

        dsk[i + 64] = esk[30 - i];
        dsk[i + 65] = esk[31 - i];
    }
}