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
struct adi {int idx; int ret; int* data; } ;

/* Variables and functions */

__attribute__((used)) static inline int adi_get_bits(struct adi *adi, int count)
{
	int bits = 0;
	int i;
	if ((adi->idx += count) > adi->ret) return 0;
	for (i = 0; i < count; i++)
		bits |= ((adi->data[adi->idx - i] >> 5) & 1) << i;
	return bits;
}