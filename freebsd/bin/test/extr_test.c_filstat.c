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
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum token { ____Placeholder_token } token ;

/* Variables and functions */
#define  FILBDEV 144 
#define  FILCDEV 143 
#define  FILDIR 142 
#define  FILEX 141 
#define  FILEXIST 140 
#define  FILFIFO 139 
#define  FILGID 138 
#define  FILGZ 137 
#define  FILRD 136 
#define  FILREG 135 
#define  FILSGID 134 
#define  FILSOCK 133 
#define  FILSTCK 132 
#define  FILSUID 131 
#define  FILSYM 130 
#define  FILUID 129 
#define  FILWR 128 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  R_OK ; 
 int S_ISBLK (int) ; 
 int S_ISCHR (int) ; 
 int S_ISDIR (int) ; 
 int S_ISFIFO (int) ; 
 int S_ISGID ; 
 int S_ISLNK (int) ; 
 int S_ISREG (int) ; 
 int S_ISSOCK (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  W_OK ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  eaccess (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int
filstat(char *nm, enum token mode)
{
	struct stat s;

	if (mode == FILSYM ? lstat(nm, &s) : stat(nm, &s))
		return 0;

	switch (mode) {
	case FILRD:
		return (eaccess(nm, R_OK) == 0);
	case FILWR:
		return (eaccess(nm, W_OK) == 0);
	case FILEX:
		/* XXX work around eaccess(2) false positives for superuser */
		if (eaccess(nm, X_OK) != 0)
			return 0;
		if (S_ISDIR(s.st_mode) || geteuid() != 0)
			return 1;
		return (s.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0;
	case FILEXIST:
		return (eaccess(nm, F_OK) == 0);
	case FILREG:
		return S_ISREG(s.st_mode);
	case FILDIR:
		return S_ISDIR(s.st_mode);
	case FILCDEV:
		return S_ISCHR(s.st_mode);
	case FILBDEV:
		return S_ISBLK(s.st_mode);
	case FILFIFO:
		return S_ISFIFO(s.st_mode);
	case FILSOCK:
		return S_ISSOCK(s.st_mode);
	case FILSYM:
		return S_ISLNK(s.st_mode);
	case FILSUID:
		return (s.st_mode & S_ISUID) != 0;
	case FILSGID:
		return (s.st_mode & S_ISGID) != 0;
	case FILSTCK:
		return (s.st_mode & S_ISVTX) != 0;
	case FILGZ:
		return s.st_size > (off_t)0;
	case FILUID:
		return s.st_uid == geteuid();
	case FILGID:
		return s.st_gid == getegid();
	default:
		return 1;
	}
}