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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  ZIP_PACKER ;
typedef  int /*<<< orphan*/  FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  FifoPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FifoSize (int /*<<< orphan*/ *) ; 
 int FileWriteAllW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZipFinish (int /*<<< orphan*/ *) ; 

bool ZipWriteW(ZIP_PACKER *p, wchar_t *name)
{
	FIFO *f;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return false;
	}

	f = ZipFinish(p);
	if (f == NULL)
	{
		return false;
	}

	return FileWriteAllW(name, FifoPtr(f), FifoSize(f));
}