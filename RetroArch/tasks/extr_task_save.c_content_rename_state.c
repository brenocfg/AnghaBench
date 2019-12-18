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
 int /*<<< orphan*/  RARCH_LOG (char*,int,char const*) ; 
 int /*<<< orphan*/  filestream_delete (char const*) ; 
 scalar_t__ filestream_exists (char const*) ; 
 int filestream_rename (char const*,char const*) ; 

bool content_rename_state(const char *origin, const char *dest)
{
   int ret = 0;
   if (filestream_exists(dest))
      filestream_delete(dest);

   ret = filestream_rename(origin, dest);
   if (!ret)
      return true;

   RARCH_LOG("Error %d renaming file %s\n", ret, origin);
   return false;
}