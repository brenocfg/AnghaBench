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
 int /*<<< orphan*/  MBEDTLS_DES_KEY_SIZE ; 
 int WEAK_KEY_COUNT ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * weak_key_table ; 

int mbedtls_des_key_check_weak( const unsigned char key[MBEDTLS_DES_KEY_SIZE] )
{
    int i;

    for( i = 0; i < WEAK_KEY_COUNT; i++ )
        if( memcmp( weak_key_table[i], key, MBEDTLS_DES_KEY_SIZE) == 0 )
            return( 1 );

    return( 0 );
}