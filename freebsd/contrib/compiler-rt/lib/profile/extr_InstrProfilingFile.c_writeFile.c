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
typedef  int /*<<< orphan*/  ProfDataWriter ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * FreeHook ; 
 int /*<<< orphan*/ * VPMergeHook ; 
 scalar_t__ doMerging () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * getFileObject (char const*) ; 
 int /*<<< orphan*/ * getProfileFile () ; 
 int /*<<< orphan*/  initFileWriter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lprofGetVPDataReader () ; 
 int /*<<< orphan*/  lprofMergeValueProfData ; 
 int /*<<< orphan*/  lprofUnlockFileHandle (int /*<<< orphan*/ *) ; 
 int lprofWriteData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * openFileForMerging (char const*,int*) ; 
 int /*<<< orphan*/  setupIOBuffer () ; 

__attribute__((used)) static int writeFile(const char *OutputName) {
  int RetVal;
  FILE *OutputFile;

  int MergeDone = 0;
  VPMergeHook = &lprofMergeValueProfData;
  if (doMerging())
    OutputFile = openFileForMerging(OutputName, &MergeDone);
  else
    OutputFile = getFileObject(OutputName);

  if (!OutputFile)
    return -1;

  FreeHook = &free;
  setupIOBuffer();
  ProfDataWriter fileWriter;
  initFileWriter(&fileWriter, OutputFile);
  RetVal = lprofWriteData(&fileWriter, lprofGetVPDataReader(), MergeDone);

  if (OutputFile == getProfileFile()) {
    fflush(OutputFile);
    if (doMerging()) {
      lprofUnlockFileHandle(OutputFile);
    }
  } else {
    fclose(OutputFile);
  }

  return RetVal;
}