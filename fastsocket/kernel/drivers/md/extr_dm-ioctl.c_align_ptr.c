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
 int ALIGN_MASK ; 

__attribute__((used)) static inline void *align_ptr(void *ptr)
{
	return (void *) (((size_t) (ptr + ALIGN_MASK)) & ~ALIGN_MASK);
}