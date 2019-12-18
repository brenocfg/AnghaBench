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
 int /*<<< orphan*/  mbedtls_sha512 (unsigned char const*,size_t,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha512_wrap( const unsigned char *input, size_t ilen,
                    unsigned char *output )
{
    mbedtls_sha512( input, ilen, output, 0 );
}