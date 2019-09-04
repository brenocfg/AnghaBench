#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_5__ {int HamMode; TYPE_1__* HamBuf; int /*<<< orphan*/  pData; } ;
struct TYPE_4__ {int /*<<< orphan*/  Size; } ;
typedef  TYPE_2__ IO ;

/* Variables and functions */
 int /*<<< orphan*/  OSFileSize (int /*<<< orphan*/ ) ; 

UINT64 FileSize64(IO *o)
{
	// Validate arguments
	if (o == NULL)
	{
		return 0;
	}

	if (o->HamMode == false)
	{
		return OSFileSize(o->pData);
	}
	else
	{
		return (UINT64)o->HamBuf->Size;
	}
}