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
typedef  unsigned char uint64_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 unsigned char MOD_ADLER ; 

uint64_t adler32(unsigned char *data, int32_t len) /* where data is the location of the data in physical memory and 
                                                       len is the length of the data in bytes */
{
    uint64_t a = 1, b = 0;
    int32_t index;
 
    /* Process each byte of the data in order */
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
 
    return (b << 16) | a;
}