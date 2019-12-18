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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int curr_chip_addx; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_DATA_HIGH ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_DATA_LOW ; 
 int chipio_send (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int chipio_write_data(struct hda_codec *codec, unsigned int data)
{
	struct ca0132_spec *spec = codec->spec;
	int res;

	/* send low 16 bits of the data */
	res = chipio_send(codec, VENDOR_CHIPIO_DATA_LOW, data & 0xffff);

	if (res != -EIO) {
		/* send high 16 bits of the data */
		res = chipio_send(codec, VENDOR_CHIPIO_DATA_HIGH,
				  data >> 16);
	}

	/*If no error encountered, automatically increment the address
	as per chip behaviour*/
	spec->curr_chip_addx = (res != -EIO) ?
					(spec->curr_chip_addx + 4) : ~0UL;
	return res;
}