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
typedef  scalar_t__ u16 ;
struct sd {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDCS_IDENT ; 
 scalar_t__ HDCS_ROWEXPH ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  stv06xx_read_sensor (struct sd*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int hdcs_dump(struct sd *sd)
{
	u16 reg, val;

	info("Dumping sensor registers:");

	for (reg = HDCS_IDENT; reg <= HDCS_ROWEXPH; reg++) {
		stv06xx_read_sensor(sd, reg, &val);
		info("reg 0x%02x = 0x%02x", reg, val);
	}
	return 0;
}