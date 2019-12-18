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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * FreeHook ; 
 int /*<<< orphan*/  PROF_WARN (char*,char const*) ; 
 int /*<<< orphan*/ * __llvm_profile_begin_orderfile () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free ; 
 int orderFileWriter (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setupIOBuffer () ; 

__attribute__((used)) static int writeOrderFile(const char *OutputName) {
  int RetVal;
  FILE *OutputFile;

  OutputFile = fopen(OutputName, "w");

  if (!OutputFile) {
    PROF_WARN("can't open file with mode ab: %s\n", OutputName);
    return -1;
  }

  FreeHook = &free;
  setupIOBuffer();
  const uint32_t *DataBegin = __llvm_profile_begin_orderfile();
  RetVal = orderFileWriter(OutputFile, DataBegin);

  fclose(OutputFile);
  return RetVal;
}