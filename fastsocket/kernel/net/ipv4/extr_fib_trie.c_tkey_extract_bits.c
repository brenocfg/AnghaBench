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
typedef  int t_key ;

/* Variables and functions */
 int KEYLENGTH ; 

__attribute__((used)) static inline t_key tkey_extract_bits(t_key a, int offset, int bits)
{
	if (offset < KEYLENGTH)
		return ((t_key)(a << offset)) >> (KEYLENGTH - bits);
	else
		return 0;
}