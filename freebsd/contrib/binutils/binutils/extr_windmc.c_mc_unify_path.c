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
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static const char *
mc_unify_path (const char *path)
{
  char *end;
  char *hsz;

  if (! path || *path == 0)
    return "./";
  hsz = xmalloc (strlen (path) + 2);
  strcpy (hsz, path);
  end = hsz + strlen (hsz);
  if (hsz[-1] != '/' && hsz[-1] != '\\')
    strcpy (end, "/");
  while ((end = strchr (hsz, '\\')) != NULL)
    *end = '/';
  return hsz;
}