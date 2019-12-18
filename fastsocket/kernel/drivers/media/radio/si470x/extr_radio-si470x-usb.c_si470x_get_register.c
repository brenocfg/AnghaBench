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
struct si470x_device {int /*<<< orphan*/ * registers; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char REGISTER_REPORT (int) ; 
 int REGISTER_REPORT_SIZE ; 
 int /*<<< orphan*/  get_unaligned_be16 (unsigned char*) ; 
 int si470x_get_report (struct si470x_device*,void*,int) ; 

int si470x_get_register(struct si470x_device *radio, int regnr)
{
	unsigned char buf[REGISTER_REPORT_SIZE];
	int retval;

	buf[0] = REGISTER_REPORT(regnr);

	retval = si470x_get_report(radio, (void *) &buf, sizeof(buf));

	if (retval >= 0)
		radio->registers[regnr] = get_unaligned_be16(&buf[1]);

	return (retval < 0) ? -EINVAL : 0;
}