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
struct dmi_header {int type; int length; } ;

/* Variables and functions */
 int* dmi_mult ; 
 int* dmi_offset ; 
 int dmi_vref ; 

__attribute__((used)) static void fschmd_dmi_decode(const struct dmi_header *header, void *dummy)
{
	int i, mult[3] = { 0 }, offset[3] = { 0 }, vref = 0, found = 0;

	/* dmi code ugliness, we get passed the address of the contents of
	   a complete DMI record, but in the form of a dmi_header pointer, in
	   reality this address holds header->length bytes of which the header
	   are the first 4 bytes */
	u8 *dmi_data = (u8 *)header;

	/* We are looking for OEM-specific type 185 */
	if (header->type != 185)
		return;

	/* we are looking for what Siemens calls "subtype" 19, the subtype
	   is stored in byte 5 of the dmi block */
	if (header->length < 5 || dmi_data[4] != 19)
		return;

	/* After the subtype comes 1 unknown byte and then blocks of 5 bytes,
	   consisting of what Siemens calls an "Entity" number, followed by
	   2 16-bit words in LSB first order */
	for (i = 6; (i + 4) < header->length; i += 5) {
		/* entity 1 - 3: voltage multiplier and offset */
		if (dmi_data[i] >= 1 && dmi_data[i] <= 3) {
			/* Our in sensors order and the DMI order differ */
			const int shuffle[3] = { 1, 0, 2 };
			int in = shuffle[dmi_data[i] - 1];

			/* Check for twice the same entity */
			if (found & (1 << in))
				return;

			mult[in] = dmi_data[i + 1] | (dmi_data[i + 2] << 8);
			offset[in] = dmi_data[i + 3] | (dmi_data[i + 4] << 8);

			found |= 1 << in;
		}

		/* entity 7: reference voltage */
		if (dmi_data[i] == 7) {
			/* Check for twice the same entity */
			if (found & 0x08)
				return;

			vref = dmi_data[i + 1] | (dmi_data[i + 2] << 8);

			found |= 0x08;
		}
	}

	if (found == 0x0F) {
		for (i = 0; i < 3; i++) {
			dmi_mult[i] = mult[i] * 10;
			dmi_offset[i] = offset[i] * 10;
		}
		/* According to the docs there should be separate dmi entries
		   for the mult's and offsets of in3-5 of the syl, but on
		   my test machine these are not present */
		dmi_mult[3] = dmi_mult[2];
		dmi_mult[4] = dmi_mult[1];
		dmi_mult[5] = dmi_mult[2];
		dmi_offset[3] = dmi_offset[2];
		dmi_offset[4] = dmi_offset[1];
		dmi_offset[5] = dmi_offset[2];
		dmi_vref = vref;
	}
}