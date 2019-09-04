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
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ IsLittleEndian () ; 
 int Swap32 (int) ; 

UINT IntToSubnetMask32(UINT i)
{
	UINT ret = 0xFFFFFFFF;

	switch (i)
	{
	case 0:		ret = 0x00000000;	break;
	case 1:		ret = 0x80000000;	break;
	case 2:		ret = 0xC0000000;	break;
	case 3:		ret = 0xE0000000;	break;
	case 4:		ret = 0xF0000000;	break;
	case 5:		ret = 0xF8000000;	break;
	case 6:		ret = 0xFC000000;	break;
	case 7:		ret = 0xFE000000;	break;
	case 8:		ret = 0xFF000000;	break;
	case 9:		ret = 0xFF800000;	break;
	case 10:	ret = 0xFFC00000;	break;
	case 11:	ret = 0xFFE00000;	break;
	case 12:	ret = 0xFFF00000;	break;
	case 13:	ret = 0xFFF80000;	break;
	case 14:	ret = 0xFFFC0000;	break;
	case 15:	ret = 0xFFFE0000;	break;
	case 16:	ret = 0xFFFF0000;	break;
	case 17:	ret = 0xFFFF8000;	break;
	case 18:	ret = 0xFFFFC000;	break;
	case 19:	ret = 0xFFFFE000;	break;
	case 20:	ret = 0xFFFFF000;	break;
	case 21:	ret = 0xFFFFF800;	break;
	case 22:	ret = 0xFFFFFC00;	break;
	case 23:	ret = 0xFFFFFE00;	break;
	case 24:	ret = 0xFFFFFF00;	break;
	case 25:	ret = 0xFFFFFF80;	break;
	case 26:	ret = 0xFFFFFFC0;	break;
	case 27:	ret = 0xFFFFFFE0;	break;
	case 28:	ret = 0xFFFFFFF0;	break;
	case 29:	ret = 0xFFFFFFF8;	break;
	case 30:	ret = 0xFFFFFFFC;	break;
	case 31:	ret = 0xFFFFFFFE;	break;
	case 32:	ret = 0xFFFFFFFF;	break;
	}

	if (IsLittleEndian())
	{
		ret = Swap32(ret);
	}

	return ret;
}