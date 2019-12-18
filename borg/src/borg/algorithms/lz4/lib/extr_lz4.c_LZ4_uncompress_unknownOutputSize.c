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
 int LZ4_decompress_safe (char const*,char*,int,int) ; 

int LZ4_uncompress_unknownOutputSize (const char* source, char* dest, int isize, int maxOutputSize)
{
    return LZ4_decompress_safe(source, dest, isize, maxOutputSize);
}