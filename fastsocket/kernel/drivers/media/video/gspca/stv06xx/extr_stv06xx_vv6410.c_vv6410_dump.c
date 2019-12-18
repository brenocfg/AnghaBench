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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,...) ; 
 int stv06xx_read_sensor (struct sd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vv6410_dump(struct sd *sd)
{
	u8 i;
	int err = 0;

	info("Dumping all vv6410 sensor registers");
	for (i = 0; i < 0xff && !err; i++) {
		u16 data;
		err = stv06xx_read_sensor(sd, i, &data);
		info("Register 0x%x contained 0x%x", i, data);
	}
	return (err < 0) ? err : 0;
}