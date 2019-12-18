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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

inline int32_t
timer_diff(uint32_t t1, uint32_t toff1, uint32_t t2, uint32_t toff2) {
	return (int32_t)((t1 + toff1) - (t2 + toff2));
}