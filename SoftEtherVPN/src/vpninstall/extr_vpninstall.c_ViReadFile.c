#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int InternetFile; scalar_t__ FileSize; scalar_t__ IoReadFileSize; int /*<<< orphan*/  hHttpFile; int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ VI_FILE ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int FileRead (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ INFINITE ; 
 int InternetReadFile (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 

UINT ViReadFile(VI_FILE *f, void *buf, UINT size)
{
	// Validate arguments
	if (f == NULL || buf == NULL)
	{
		return INFINITE;
	}

	if (f->InternetFile == false)
	{
		UINT readsize = MIN(size, f->FileSize - f->IoReadFileSize);
		bool ret;

		if (readsize == 0)
		{
			return 0;
		}

		ret = FileRead(f->io, buf, readsize);

		if (ret == false)
		{
			return INFINITE;
		}

		f->IoReadFileSize += readsize;

		return readsize;
	}
	else
	{
		UINT readsize = 0;

		if (InternetReadFile(f->hHttpFile, buf, size, &readsize) == false)
		{
			return INFINITE;
		}

		return readsize;
	}
}