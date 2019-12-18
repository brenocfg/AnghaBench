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
struct mpu_config {int version; int revision; } ;

/* Variables and functions */
 int mpu_cmd (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpu401_chk_version(int n, struct mpu_config *devc)
{
	int tmp;

	devc->version = devc->revision = 0;

	tmp = mpu_cmd(n, 0xAC, 0);
	if (tmp < 0)
		return;
	if ((tmp & 0xf0) > 0x20)	/* Why it's larger than 2.x ??? */
		return;
	devc->version = tmp;

	if ((tmp = mpu_cmd(n, 0xAD, 0)) < 0) {
		devc->version = 0;
		return;
	}
	devc->revision = tmp;
}