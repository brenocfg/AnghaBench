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
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_pal_prefetch_visibility (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remote_pal_prefetch_visibility(void *v)
{
	s64 trans_type = (s64)v;
	ia64_pal_prefetch_visibility(trans_type);
}