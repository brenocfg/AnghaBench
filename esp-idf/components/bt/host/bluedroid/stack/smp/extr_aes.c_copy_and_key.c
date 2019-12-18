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
typedef  int uint_8t ;
typedef  int uint_32t ;

/* Variables and functions */
 int /*<<< orphan*/  block_copy (void*,void const*) ; 
 int /*<<< orphan*/  xor_block (void*,void const*) ; 

__attribute__((used)) static void copy_and_key( void *d, const void *s, const void *k )
{
#if defined( HAVE_UINT_32T )
    ((uint_32t *)d)[ 0] = ((uint_32t *)s)[ 0] ^ ((uint_32t *)k)[ 0];
    ((uint_32t *)d)[ 1] = ((uint_32t *)s)[ 1] ^ ((uint_32t *)k)[ 1];
    ((uint_32t *)d)[ 2] = ((uint_32t *)s)[ 2] ^ ((uint_32t *)k)[ 2];
    ((uint_32t *)d)[ 3] = ((uint_32t *)s)[ 3] ^ ((uint_32t *)k)[ 3];
#elif 1
    ((uint_8t *)d)[ 0] = ((uint_8t *)s)[ 0] ^ ((uint_8t *)k)[ 0];
    ((uint_8t *)d)[ 1] = ((uint_8t *)s)[ 1] ^ ((uint_8t *)k)[ 1];
    ((uint_8t *)d)[ 2] = ((uint_8t *)s)[ 2] ^ ((uint_8t *)k)[ 2];
    ((uint_8t *)d)[ 3] = ((uint_8t *)s)[ 3] ^ ((uint_8t *)k)[ 3];
    ((uint_8t *)d)[ 4] = ((uint_8t *)s)[ 4] ^ ((uint_8t *)k)[ 4];
    ((uint_8t *)d)[ 5] = ((uint_8t *)s)[ 5] ^ ((uint_8t *)k)[ 5];
    ((uint_8t *)d)[ 6] = ((uint_8t *)s)[ 6] ^ ((uint_8t *)k)[ 6];
    ((uint_8t *)d)[ 7] = ((uint_8t *)s)[ 7] ^ ((uint_8t *)k)[ 7];
    ((uint_8t *)d)[ 8] = ((uint_8t *)s)[ 8] ^ ((uint_8t *)k)[ 8];
    ((uint_8t *)d)[ 9] = ((uint_8t *)s)[ 9] ^ ((uint_8t *)k)[ 9];
    ((uint_8t *)d)[10] = ((uint_8t *)s)[10] ^ ((uint_8t *)k)[10];
    ((uint_8t *)d)[11] = ((uint_8t *)s)[11] ^ ((uint_8t *)k)[11];
    ((uint_8t *)d)[12] = ((uint_8t *)s)[12] ^ ((uint_8t *)k)[12];
    ((uint_8t *)d)[13] = ((uint_8t *)s)[13] ^ ((uint_8t *)k)[13];
    ((uint_8t *)d)[14] = ((uint_8t *)s)[14] ^ ((uint_8t *)k)[14];
    ((uint_8t *)d)[15] = ((uint_8t *)s)[15] ^ ((uint_8t *)k)[15];
#else
    block_copy(d, s);
    xor_block(d, k);
#endif
}