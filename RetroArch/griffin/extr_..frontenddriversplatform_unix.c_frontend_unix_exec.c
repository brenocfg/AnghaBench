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
 int /*<<< orphan*/  execv (char const*,char**) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void frontend_unix_exec(const char *path, bool should_load_game)
{
   char *newargv[]    = { NULL, NULL };
   size_t len         = strlen(path);

   newargv[0] = (char*)malloc(len);

   strlcpy(newargv[0], path, len);

   execv(path, newargv);
}