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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_COMMON ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  call_init (int /*<<< orphan*/ *,int,char const**) ; 
 int errno ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int libretrodb_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_dofile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaL_dostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  value_provider ; 

int main(int argc, char ** argv)
{
   lua_State *L;
   const char *db_file;
   const char *lua_file;
   RFILE *dst;
   int rv = 0;

   if (argc < 3)
   {
      printf("usage:\n%s <db file> <lua file> [args ...]\n", argv[0]);
      return 1;
   }

   db_file  = argv[1];
   lua_file = argv[2];
   L        = luaL_newstate();

   luaL_openlibs(L);
   luaL_dostring(L, LUA_COMMON);

   if (luaL_dofile(L, lua_file) != 0)
      return 1;

   call_init(L, argc - 2, (const char **) argv + 2);

   dst = filestream_open(db_file,
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!dst)
   {
      printf(
            "Could not open destination file '%s': %s\n",
            db_file,
            strerror(errno)
            );
      rv = errno;
      goto clean;
   }

   rv = libretrodb_create(dst, &value_provider, L);

clean:
   lua_close(L);
   filestream_close(dst);
   return rv;
}