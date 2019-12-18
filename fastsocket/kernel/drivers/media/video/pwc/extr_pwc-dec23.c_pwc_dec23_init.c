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
struct pwc_device {struct pwc_dec23_private* decompress_data; } ;
struct pwc_dec23_private {int nbits; int nbitsmask; scalar_t__ scalebits; int /*<<< orphan*/  table_8004_pass2; int /*<<< orphan*/  table_0004_pass2; int /*<<< orphan*/  table_8004_pass1; int /*<<< orphan*/  table_0004_pass1; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC3 (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ ** KiaraRomTable ; 
 int MAX_OUTER_CROP_VALUE ; 
 scalar_t__ SCALEBITS ; 
 int /*<<< orphan*/ ** TimonRomTable ; 
 int /*<<< orphan*/  build_bit_powermask_table (struct pwc_dec23_private*) ; 
 int /*<<< orphan*/  build_subblock_pattern (struct pwc_dec23_private*) ; 
 int /*<<< orphan*/  build_table_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_table_dc00_d800 (struct pwc_dec23_private*) ; 
 struct pwc_dec23_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int* pwc_crop_table ; 

int pwc_dec23_init(struct pwc_device *pwc, int type, unsigned char *cmd)
{
	int flags, version, shift, i;
	struct pwc_dec23_private *pdec;

	if (pwc->decompress_data == NULL) {
		pdec = kmalloc(sizeof(struct pwc_dec23_private), GFP_KERNEL);
		if (pdec == NULL)
			return -ENOMEM;
		pwc->decompress_data = pdec;
	}
	pdec = pwc->decompress_data;

	if (DEVICE_USE_CODEC3(type)) {
		flags = cmd[2] & 0x18;
		if (flags == 8)
			pdec->nbits = 7;	/* More bits, mean more bits to encode the stream, but better quality */
		else if (flags == 0x10)
			pdec->nbits = 8;
		else
			pdec->nbits = 6;

		version = cmd[2] >> 5;
		build_table_color(KiaraRomTable[version][0], pdec->table_0004_pass1, pdec->table_8004_pass1);
		build_table_color(KiaraRomTable[version][1], pdec->table_0004_pass2, pdec->table_8004_pass2);

	} else {

		flags = cmd[2] & 6;
		if (flags == 2)
			pdec->nbits = 7;
		else if (flags == 4)
			pdec->nbits = 8;
		else
			pdec->nbits = 6;

		version = cmd[2] >> 3;
		build_table_color(TimonRomTable[version][0], pdec->table_0004_pass1, pdec->table_8004_pass1);
		build_table_color(TimonRomTable[version][1], pdec->table_0004_pass2, pdec->table_8004_pass2);
	}

	/* Informations can be coded on a variable number of bits but never less than 8 */
	shift = 8 - pdec->nbits;
	pdec->scalebits = SCALEBITS - shift;
	pdec->nbitsmask = 0xFF >> shift;

	fill_table_dc00_d800(pdec);
	build_subblock_pattern(pdec);
	build_bit_powermask_table(pdec);

#if USE_LOOKUP_TABLE_TO_CLAMP
	/* Build the static table to clamp value [0-255] */
	for (i=0;i<MAX_OUTER_CROP_VALUE;i++)
		pwc_crop_table[i] = 0;
	for (i=0; i<256; i++)
		pwc_crop_table[MAX_OUTER_CROP_VALUE+i] = i;
	for (i=0; i<MAX_OUTER_CROP_VALUE; i++)
		pwc_crop_table[MAX_OUTER_CROP_VALUE+256+i] = 255;
#endif

	return 0;
}