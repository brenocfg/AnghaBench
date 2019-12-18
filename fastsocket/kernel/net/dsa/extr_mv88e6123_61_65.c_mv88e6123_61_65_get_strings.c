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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6123_61_65_hw_stats ; 
 int /*<<< orphan*/  mv88e6xxx_get_strings (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mv88e6123_61_65_get_strings(struct dsa_switch *ds, int port, uint8_t *data)
{
	mv88e6xxx_get_strings(ds, ARRAY_SIZE(mv88e6123_61_65_hw_stats),
			      mv88e6123_61_65_hw_stats, port, data);
}