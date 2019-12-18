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
typedef  unsigned int UBYTE ;

/* Variables and functions */
 scalar_t__ GZWRITE (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  GetGZErrorText () ; 
 int /*<<< orphan*/  StateFile ; 
 scalar_t__ Z_OK ; 
 scalar_t__ nFileError ; 

void StateSav_SaveINT(const int *data, int num)
{
	if (!StateFile || nFileError != Z_OK)
		return;

	/* INTs are always saved as 32bits (4 bytes) in the file. They can be any size
	   on the platform however. The sign bit is clobbered into the fourth byte saved
	   for each int; on read it will be extended out to its proper position for the
	   native INT size */
	while (num > 0) {
		UBYTE signbit = 0;
		unsigned int temp;
		UBYTE byte;
		int temp0;

		temp0 = *data++;
		if (temp0 < 0) {
			temp0 = -temp0;
			signbit = 0x80;
		}
		temp = (unsigned int) temp0;

		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = (temp & 0x7f) | signbit;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		num--;
	}
}