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
struct dm_thin_device {scalar_t__ snapshotted_time; } ;

/* Variables and functions */

__attribute__((used)) static bool __snapshotted_since(struct dm_thin_device *td, uint32_t time)
{
	return td->snapshotted_time > time;
}