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
struct TYPE_2__ {scalar_t__ MergePoolSize; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ COMPILER_RT_ALLOCA (int) ; 
 int /*<<< orphan*/  createProfileDir (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getCurFilename (char*,int /*<<< orphan*/ ) ; 
 int getCurFilenameLength () ; 
 TYPE_1__ lprofCurFilename ; 

__attribute__((used)) static void truncateCurrentFile(void) {
  const char *Filename;
  char *FilenameBuf;
  FILE *File;
  int Length;

  Length = getCurFilenameLength();
  FilenameBuf = (char *)COMPILER_RT_ALLOCA(Length + 1);
  Filename = getCurFilename(FilenameBuf, 0);
  if (!Filename)
    return;

  /* By pass file truncation to allow online raw profile
   * merging. */
  if (lprofCurFilename.MergePoolSize)
    return;

  createProfileDir(Filename);

  /* Truncate the file.  Later we'll reopen and append. */
  File = fopen(Filename, "w");
  if (!File)
    return;
  fclose(File);
}