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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int detected_redzone_corruption ; 

__attribute__((used)) static void
arena_redzone_corruption_replacement(void *ptr, size_t usize, bool after,
    size_t offset, uint8_t byte)
{

	detected_redzone_corruption = true;
}