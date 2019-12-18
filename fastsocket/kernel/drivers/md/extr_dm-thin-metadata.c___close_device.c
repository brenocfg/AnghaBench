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
struct dm_thin_device {int /*<<< orphan*/  open_count; } ;

/* Variables and functions */

__attribute__((used)) static void __close_device(struct dm_thin_device *td)
{
	--td->open_count;
}