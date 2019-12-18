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
struct cpx {int dummy; } ;

/* Variables and functions */

size_t cpx_size(size_t key_size)
{
	size_t size = sizeof(struct cpx) + key_size;

#if DEBUG
	size += 4; // Extra for magic
#endif

	return size;
}