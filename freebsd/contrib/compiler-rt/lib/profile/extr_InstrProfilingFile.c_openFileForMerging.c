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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ COMPILER_RT_FTRUNCATE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  PROF_ERR (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  createProfileDir (char const*) ; 
 int doProfileMerging (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getProfileFile () ; 
 int /*<<< orphan*/  lprofLockFileHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lprofOpenFileEx (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *openFileForMerging(const char *ProfileFileName, int *MergeDone) {
  FILE *ProfileFile = NULL;
  int rc;

  ProfileFile = getProfileFile();
  if (ProfileFile) {
    lprofLockFileHandle(ProfileFile);
  } else {
    createProfileDir(ProfileFileName);
    ProfileFile = lprofOpenFileEx(ProfileFileName);
  }
  if (!ProfileFile)
    return NULL;

  rc = doProfileMerging(ProfileFile, MergeDone);
  if (rc || (!*MergeDone && COMPILER_RT_FTRUNCATE(ProfileFile, 0L)) ||
      fseek(ProfileFile, 0L, SEEK_SET) == -1) {
    PROF_ERR("Profile Merging of file %s failed: %s\n", ProfileFileName,
             strerror(errno));
    fclose(ProfileFile);
    return NULL;
  }
  return ProfileFile;
}