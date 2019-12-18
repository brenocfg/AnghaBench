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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ GZREAD (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  GetGZErrorText () ; 
 int /*<<< orphan*/  StateFile ; 
 scalar_t__ Z_OK ; 
 scalar_t__ nFileError ; 

void StateSav_ReadINT(int *data, int num)
{
	if (!StateFile || nFileError != Z_OK)
		return;

	while (num > 0) {
		UBYTE signbit = 0;
		int temp;
		UBYTE byte1, byte2, byte3, byte4;

		if (GZREAD(StateFile, &byte1, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte2, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte3, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte4, 1) == 0) {
			GetGZErrorText();
			break;
		}

		signbit = byte4 & 0x80;
		byte4 &= 0x7f;

		temp = (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
		if (signbit)
			temp = -temp;
		*data++ = temp;

		num--;
	}
}