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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  thread_set_tag_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint16_t
thread_set_tag(thread_t th, uint16_t tag)
{
	return thread_set_tag_internal(th, tag);
}