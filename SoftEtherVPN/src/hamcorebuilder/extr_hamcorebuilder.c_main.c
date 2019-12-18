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

/* Variables and functions */
 int /*<<< orphan*/  BuildHamcore (char*,char*,int) ; 
 int /*<<< orphan*/  FreeCedar () ; 
 int /*<<< orphan*/  FreeMayaqua () ; 
 int /*<<< orphan*/  InitCedar () ; 
 int /*<<< orphan*/  InitMayaqua (int,int,int,char**) ; 
 int /*<<< orphan*/  MayaquaMinimalMode () ; 
 int /*<<< orphan*/  Print (char*,...) ; 

int main(int argc, char *argv[])
{
	MayaquaMinimalMode();

#if defined(_DEBUG) || defined(DEBUG)	// In VC++ compilers, the macro is "_DEBUG", not "DEBUG".
	// If set memcheck = true, the program will be vitally slow since it will log all malloc() / realloc() / free() calls to find the cause of memory leak.
	// For normal debug we set memcheck = false.
	// Please set memcheck = true if you want to test the cause of memory leaks.
	InitMayaqua(false, true, argc, argv);
#else
	InitMayaqua(false, false, argc, argv);
#endif
	InitCedar();

	Print("hamcore.se2 Build Utility\n");
	Print("Copyright (c) SoftEther VPN Project. All Rights Reserved.\n\n");

	if (argc < 3)
	{
		Print("Usage: hamcorebuilder <src_dir> <dest_hamcore_filename>\n\n");
	}
	else
	{
		char *src_dir = argv[1];
		char *dst_filename = argv[2];

		Print("Src Dir: '%s'\n", src_dir);
		Print("Dest Filename: '%s'\n", dst_filename);

		Print("\nProcessing...\n");

#ifdef	WIN32
		BuildHamcore(dst_filename, src_dir, false);
#else
		BuildHamcore(dst_filename, src_dir, true);
#endif

		Print("\nDone.\n");
	}

	FreeCedar();
	FreeMayaqua();

	return 0;
}