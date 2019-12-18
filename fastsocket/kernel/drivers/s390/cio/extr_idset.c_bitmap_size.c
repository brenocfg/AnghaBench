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
 int __BITOPS_WORDS (int) ; 

__attribute__((used)) static inline unsigned long bitmap_size(int num_ssid, int num_id)
{
	return __BITOPS_WORDS(num_ssid * num_id) * sizeof(unsigned long);
}