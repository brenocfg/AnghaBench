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
 scalar_t__ COMPILER_RT_ALLOCA (size_t) ; 
 int /*<<< orphan*/  __llvm_profile_recursive_mkdir (char*) ; 
 scalar_t__ lprofFindFirstDirSeparator (char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void createProfileDir(const char *Filename) {
  size_t Length = strlen(Filename);
  if (lprofFindFirstDirSeparator(Filename)) {
    char *Copy = (char *)COMPILER_RT_ALLOCA(Length + 1);
    strncpy(Copy, Filename, Length + 1);
    __llvm_profile_recursive_mkdir(Copy);
  }
}