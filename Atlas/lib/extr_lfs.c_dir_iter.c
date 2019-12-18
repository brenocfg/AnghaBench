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
struct dirent {int /*<<< orphan*/  d_name; } ;
struct _finddata_t {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int closed; long hFile; int /*<<< orphan*/  dir; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__ dir_data ;

/* Variables and functions */
 int /*<<< orphan*/  _findclose (long) ; 
 long _findfirst (int /*<<< orphan*/ ,struct _finddata_t*) ; 
 long _findnext (long,struct _finddata_t*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dir_iter (lua_State *L) {
#ifdef _WIN32
	struct _finddata_t c_file;
#else
	struct dirent *entry;
#endif
	dir_data *d = (dir_data *)lua_touserdata (L, lua_upvalueindex (1));
	luaL_argcheck (L, !d->closed, 1, "closed directory");
#ifdef _WIN32
	if (d->hFile == 0L) { /* first entry */
		if ((d->hFile = _findfirst (d->pattern, &c_file)) == -1L) {
			lua_pushnil (L);
			lua_pushstring (L, strerror (errno));
			return 2;
		} else {
			lua_pushstring (L, c_file.name);
			return 1;
		}
	} else { /* next entry */
		if (_findnext (d->hFile, &c_file) == -1L) {
			/* no more entries => close directory */
			_findclose (d->hFile);
			d->closed = 1;
			return 0;
		} else {
			lua_pushstring (L, c_file.name);
			return 1;
		}
	}
#else
	if ((entry = readdir (d->dir)) != NULL) {
		lua_pushstring (L, entry->d_name);
		return 1;
	} else {
		/* no more entries => close directory */
		closedir (d->dir);
		d->closed = 1;
		return 0;
	}
#endif
}