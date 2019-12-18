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
struct wf_sensor {int dummy; } ;
struct wf_6690_sensor {int /*<<< orphan*/ * i2c; } ;
typedef  int s32 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MAX6690_EXTERNAL_TEMP ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wf_6690_sensor* wf_to_6690 (struct wf_sensor*) ; 

__attribute__((used)) static int wf_max6690_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_6690_sensor *max = wf_to_6690(sr);
	s32 data;

	if (max->i2c == NULL)
		return -ENODEV;

	/* chip gets initialized by firmware */
	data = i2c_smbus_read_byte_data(max->i2c, MAX6690_EXTERNAL_TEMP);
	if (data < 0)
		return data;
	*value = data << 16;
	return 0;
}