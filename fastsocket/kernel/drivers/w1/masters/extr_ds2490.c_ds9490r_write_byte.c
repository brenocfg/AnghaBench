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
typedef  int /*<<< orphan*/  u8 ;
struct ds_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_write_byte (struct ds_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds9490r_write_byte(void *data, u8 byte)
{
	struct ds_device *dev = data;

	ds_write_byte(dev, byte);
}