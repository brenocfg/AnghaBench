#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int w; int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char const*) ; 
 int /*<<< orphan*/  ExtractFileExtension (char const*,char*) ; 
 int /*<<< orphan*/  LoadBMP (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  LoadLBM (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LoadPCX (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 TYPE_1__ bmhd ; 

void Load256Image (const char *name, byte **pixels, byte **palette,
				   int *width, int *height)
{
	char	ext[128];

	ExtractFileExtension (name, ext);
	if (!Q_stricmp (ext, "lbm"))
	{
		LoadLBM (name, pixels, palette);
		if (width)
			*width = bmhd.w;
		if (height)
			*height = bmhd.h;
	}
	else if (!Q_stricmp (ext, "pcx"))
	{
		LoadPCX (name, pixels, palette, width, height);
	}
	else if (!Q_stricmp (ext, "bmp"))
	{
		LoadBMP (name, pixels, palette, width, height);
	}
	else
		Error ("%s doesn't have a known image extension", name);
}