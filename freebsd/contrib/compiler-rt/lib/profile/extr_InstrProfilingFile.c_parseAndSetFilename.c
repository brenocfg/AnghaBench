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
struct TYPE_2__ {char* FilenamePat; scalar_t__ PNS; } ;
typedef  scalar_t__ ProfileNameSpecifier ;

/* Variables and functions */
 char* DefaultProfileName ; 
 int /*<<< orphan*/  PROF_NOTE (char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  getPNSStr (scalar_t__) ; 
 scalar_t__ getenv (char*) ; 
 TYPE_1__ lprofCurFilename ; 
 scalar_t__ parseFilenamePattern (char const*,unsigned int) ; 
 int /*<<< orphan*/  resetFilenameToDefault () ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  truncateCurrentFile () ; 

__attribute__((used)) static void parseAndSetFilename(const char *FilenamePat,
                                ProfileNameSpecifier PNS,
                                unsigned CopyFilenamePat) {

  const char *OldFilenamePat = lprofCurFilename.FilenamePat;
  ProfileNameSpecifier OldPNS = lprofCurFilename.PNS;

  if (PNS < OldPNS)
    return;

  if (!FilenamePat)
    FilenamePat = DefaultProfileName;

  if (OldFilenamePat && !strcmp(OldFilenamePat, FilenamePat)) {
    lprofCurFilename.PNS = PNS;
    return;
  }

  /* When PNS >= OldPNS, the last one wins. */
  if (!FilenamePat || parseFilenamePattern(FilenamePat, CopyFilenamePat))
    resetFilenameToDefault();
  lprofCurFilename.PNS = PNS;

  if (!OldFilenamePat) {
    if (getenv("LLVM_PROFILE_VERBOSE"))
      PROF_NOTE("Set profile file path to \"%s\" via %s.\n",
                lprofCurFilename.FilenamePat, getPNSStr(PNS));
  } else {
    if (getenv("LLVM_PROFILE_VERBOSE"))
      PROF_NOTE("Override old profile path \"%s\" via %s to \"%s\" via %s.\n",
                OldFilenamePat, getPNSStr(OldPNS), lprofCurFilename.FilenamePat,
                getPNSStr(PNS));
  }

  truncateCurrentFile();
}