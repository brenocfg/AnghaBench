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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int dspio_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dspio_write_multiple(struct hda_codec *codec,
				unsigned int *buffer, unsigned int size)
{
	int status = 0;
	unsigned int count;

	if ((buffer == NULL))
		return -EINVAL;

	count = 0;
	while (count < size) {
		status = dspio_write(codec, *buffer++);
		if (status != 0)
			break;
		count++;
	}

	return status;
}