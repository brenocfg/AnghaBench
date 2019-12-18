#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct tcm825x_sensor {TYPE_1__* i2c_client; } ;
typedef  enum image_size { ____Placeholder_image_size } image_size ;
struct TYPE_4__ {unsigned long height; unsigned long width; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VGA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int subQCIF ; 
 TYPE_2__* tcm825x_sizes ; 

__attribute__((used)) static enum image_size tcm825x_find_size(struct v4l2_int_device *s,
					 unsigned int width,
					 unsigned int height)
{
	enum image_size isize;
	unsigned long pixels = width * height;
	struct tcm825x_sensor *sensor = s->priv;

	for (isize = subQCIF; isize < VGA; isize++) {
		if (tcm825x_sizes[isize + 1].height
		    * tcm825x_sizes[isize + 1].width > pixels) {
			dev_dbg(&sensor->i2c_client->dev, "size %d\n", isize);

			return isize;
		}
	}

	dev_dbg(&sensor->i2c_client->dev, "format default VGA\n");

	return VGA;
}