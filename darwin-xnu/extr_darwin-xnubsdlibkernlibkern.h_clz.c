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
typedef  int /*<<< orphan*/  num ;

/* Variables and functions */
 int CHAR_BIT ; 
 int __builtin_clz (unsigned int) ; 

__attribute__((used)) static inline int
clz(unsigned int num)
{
#if (__arm__ || __arm64__)
	// On ARM, clz(0) is defined to return number of bits in the input type
	return __builtin_clz(num);
#else
	// On Intel, clz(0) is undefined
	return num ? __builtin_clz(num) : sizeof(num) * CHAR_BIT;
#endif
}