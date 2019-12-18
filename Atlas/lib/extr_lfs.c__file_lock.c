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
struct flock {void* l_len; void* l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
typedef  void* off_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int LK_NBLCK ; 
 int LK_UNLCK ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _locking (int /*<<< orphan*/ ,int,long) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long const,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int _file_lock (lua_State *L, FILE *fh, const char *mode, const long start, long len, const char *funcname) {
	int code;
#ifdef _WIN32
	/* lkmode valid values are:
	   LK_LOCK    Locks the specified bytes. If the bytes cannot be locked, the program immediately tries again after 1 second. If, after 10 attempts, the bytes cannot be locked, the constant returns an error.
	   LK_NBLCK   Locks the specified bytes. If the bytes cannot be locked, the constant returns an error.
	   LK_NBRLCK  Same as _LK_NBLCK.
	   LK_RLCK    Same as _LK_LOCK.
	   LK_UNLCK   Unlocks the specified bytes, which must have been previously locked.

	   Regions should be locked only briefly and should be unlocked before closing a file or exiting the program.

	   http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclib/html/_crt__locking.asp
	*/
	int lkmode;
	switch (*mode) {
		case 'r': lkmode = LK_NBLCK; break;
		case 'w': lkmode = LK_NBLCK; break;
		case 'u': lkmode = LK_UNLCK; break;
		default : return luaL_error (L, "%s: invalid mode", funcname);
	}
	if (!len) {
		fseek (fh, 0L, SEEK_END);
		len = ftell (fh);
	}
	fseek (fh, start, SEEK_SET);
	code = _locking (fileno(fh), lkmode, len);
#else
	struct flock f;
	switch (*mode) {
		case 'w': f.l_type = F_WRLCK; break;
		case 'r': f.l_type = F_RDLCK; break;
		case 'u': f.l_type = F_UNLCK; break;
		default : return luaL_error (L, "%s: invalid mode", funcname);
	}
	f.l_whence = SEEK_SET;
	f.l_start = (off_t)start;
	f.l_len = (off_t)len;
	code = fcntl (fileno(fh), F_SETLK, &f);
#endif
	return (code != -1);
}