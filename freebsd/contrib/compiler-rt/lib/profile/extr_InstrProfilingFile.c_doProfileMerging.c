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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  __llvm_profile_header ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_RT_FTRUNCATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* MAP_FAILED ; 
 int MAP_FILE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  PROF_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROF_WARN (char*,char*) ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ __llvm_profile_check_compatibility (char*,int) ; 
 int /*<<< orphan*/  __llvm_profile_get_size_for_buffer () ; 
 int /*<<< orphan*/  __llvm_profile_merge_from_buffer (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 char* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doProfileMerging(FILE *ProfileFile, int *MergeDone) {
  uint64_t ProfileFileSize;
  char *ProfileBuffer;

  if (fseek(ProfileFile, 0L, SEEK_END) == -1) {
    PROF_ERR("Unable to merge profile data, unable to get size: %s\n",
             strerror(errno));
    return -1;
  }
  ProfileFileSize = ftell(ProfileFile);

  /* Restore file offset.  */
  if (fseek(ProfileFile, 0L, SEEK_SET) == -1) {
    PROF_ERR("Unable to merge profile data, unable to rewind: %s\n",
             strerror(errno));
    return -1;
  }

  /* Nothing to merge.  */
  if (ProfileFileSize < sizeof(__llvm_profile_header)) {
    if (ProfileFileSize)
      PROF_WARN("Unable to merge profile data: %s\n",
                "source profile file is too small.");
    return 0;
  }

  ProfileBuffer = mmap(NULL, ProfileFileSize, PROT_READ, MAP_SHARED | MAP_FILE,
                       fileno(ProfileFile), 0);
  if (ProfileBuffer == MAP_FAILED) {
    PROF_ERR("Unable to merge profile data, mmap failed: %s\n",
             strerror(errno));
    return -1;
  }

  if (__llvm_profile_check_compatibility(ProfileBuffer, ProfileFileSize)) {
    (void)munmap(ProfileBuffer, ProfileFileSize);
    PROF_WARN("Unable to merge profile data: %s\n",
              "source profile file is not compatible.");
    return 0;
  }

  /* Now start merging */
  __llvm_profile_merge_from_buffer(ProfileBuffer, ProfileFileSize);

  // Truncate the file in case merging of value profile did not happend to
  // prevent from leaving garbage data at the end of the profile file.
  COMPILER_RT_FTRUNCATE(ProfileFile, __llvm_profile_get_size_for_buffer());

  (void)munmap(ProfileBuffer, ProfileFileSize);
  *MergeDone = 1;

  return 0;
}