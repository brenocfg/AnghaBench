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
typedef  int /*<<< orphan*/  uint_8t ;
typedef  int /*<<< orphan*/  uint_32t ;

/* Variables and functions */

__attribute__((used)) static void xor_block( void *d, const void *s )
{
#if defined( HAVE_UINT_32T )
    ((uint_32t *)d)[ 0] ^= ((uint_32t *)s)[ 0];
    ((uint_32t *)d)[ 1] ^= ((uint_32t *)s)[ 1];
    ((uint_32t *)d)[ 2] ^= ((uint_32t *)s)[ 2];
    ((uint_32t *)d)[ 3] ^= ((uint_32t *)s)[ 3];
#else
    ((uint_8t *)d)[ 0] ^= ((uint_8t *)s)[ 0];
    ((uint_8t *)d)[ 1] ^= ((uint_8t *)s)[ 1];
    ((uint_8t *)d)[ 2] ^= ((uint_8t *)s)[ 2];
    ((uint_8t *)d)[ 3] ^= ((uint_8t *)s)[ 3];
    ((uint_8t *)d)[ 4] ^= ((uint_8t *)s)[ 4];
    ((uint_8t *)d)[ 5] ^= ((uint_8t *)s)[ 5];
    ((uint_8t *)d)[ 6] ^= ((uint_8t *)s)[ 6];
    ((uint_8t *)d)[ 7] ^= ((uint_8t *)s)[ 7];
    ((uint_8t *)d)[ 8] ^= ((uint_8t *)s)[ 8];
    ((uint_8t *)d)[ 9] ^= ((uint_8t *)s)[ 9];
    ((uint_8t *)d)[10] ^= ((uint_8t *)s)[10];
    ((uint_8t *)d)[11] ^= ((uint_8t *)s)[11];
    ((uint_8t *)d)[12] ^= ((uint_8t *)s)[12];
    ((uint_8t *)d)[13] ^= ((uint_8t *)s)[13];
    ((uint_8t *)d)[14] ^= ((uint_8t *)s)[14];
    ((uint_8t *)d)[15] ^= ((uint_8t *)s)[15];
#endif
}