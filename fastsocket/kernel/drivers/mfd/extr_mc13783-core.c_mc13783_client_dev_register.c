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
struct mfd_cell {char const* name; } ;
struct mc13783 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfd_add_devices (int /*<<< orphan*/ ,int,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mc13783_client_dev_register(struct mc13783 *mc13783,
				       const char *name)
{
	struct mfd_cell cell = {};

	cell.name = name;

	mfd_add_devices(mc13783->dev, -1, &cell, 1, NULL, 0);
}