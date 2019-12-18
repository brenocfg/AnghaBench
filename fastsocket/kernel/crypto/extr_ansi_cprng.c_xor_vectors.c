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

__attribute__((used)) static void xor_vectors(unsigned char *in1, unsigned char *in2,
			unsigned char *out, unsigned int size)
{
	int i;

	for (i = 0; i < size; i++)
		out[i] = in1[i] ^ in2[i];

}