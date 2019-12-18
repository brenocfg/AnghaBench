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
 int MBEDTLS_DES_KEY_SIZE ; 
 unsigned char* odd_parity_table ; 

void mbedtls_des_key_set_parity( unsigned char key[MBEDTLS_DES_KEY_SIZE] )
{
    int i;

    for( i = 0; i < MBEDTLS_DES_KEY_SIZE; i++ )
        key[i] = odd_parity_table[key[i] / 2];
}