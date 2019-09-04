#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ulk_pid; scalar_t__ ulk_addr; } ;
typedef  TYPE_1__ ulk_t ;

/* Variables and functions */

__attribute__((used)) inline static bool
ull_key_match(ulk_t *a, ulk_t *b)
{
	return ((a->ulk_pid == b->ulk_pid) &&
		(a->ulk_addr == b->ulk_addr));
}