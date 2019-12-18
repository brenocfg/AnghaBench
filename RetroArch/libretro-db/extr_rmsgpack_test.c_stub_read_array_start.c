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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub_state_push_array (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stub_read_array_start(uint32_t size, void *data)
{
	stub_state_push_array(data, size);
	return 0;
}