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
typedef  int UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ GZWRITE (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  GetGZErrorText () ; 
 int /*<<< orphan*/  StateFile ; 
 scalar_t__ Z_OK ; 
 scalar_t__ nFileError ; 

void StateSav_SaveUWORD(const UWORD *data, int num)
{
	if (!StateFile || nFileError != Z_OK)
		return;

	/* UWORDS are saved as 16bits, regardless of the size on this particular
	   platform. Each byte of the UWORD will be pushed out individually in
	   LSB order. The shifts here and in the read routines will work for both
	   LSB and MSB architectures. */
	while (num > 0) {
		UWORD temp;
		UBYTE byte;

		temp = *data++;
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
		num--;
	}
}