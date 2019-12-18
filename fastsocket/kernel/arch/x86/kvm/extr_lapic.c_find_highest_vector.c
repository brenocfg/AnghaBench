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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int MAX_APIC_VECTOR ; 
 int fls (scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int find_highest_vector(void *bitmap)
{
	u32 *word = bitmap;
	int word_offset = MAX_APIC_VECTOR >> 5;

	while ((word_offset != 0) && (word[(--word_offset) << 2] == 0))
		continue;

	if (likely(!word_offset && !word[0]))
		return -1;
	else
		return fls(word[word_offset << 2]) - 1 + (word_offset << 5);
}