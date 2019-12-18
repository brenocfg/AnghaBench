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
 int /*<<< orphan*/  VENDOR_CHIPIO_HIC_POST_READ ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_HIC_READ_DATA ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_STATUS ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int chipio_send (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chipio_read_data(struct hda_codec *codec, unsigned int *data)
{
	struct ca0132_spec *spec = codec->spec;
	int res;

	/* post read */
	res = chipio_send(codec, VENDOR_CHIPIO_HIC_POST_READ, 0);

	if (res != -EIO) {
		/* read status */
		res = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	}

	if (res != -EIO) {
		/* read data */
		*data = snd_hda_codec_read(codec, WIDGET_CHIP_CTRL, 0,
					   VENDOR_CHIPIO_HIC_READ_DATA,
					   0);
	}

	/*If no error encountered, automatically increment the address
	as per chip behaviour*/
	spec->curr_chip_addx = (res != -EIO) ?
					(spec->curr_chip_addx + 4) : ~0UL;
	return res;
}