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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mcset_mc_basename ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static FILE *
mc_create_path_text_file (const char *path, const char *ext)
{
  FILE *ret;
  size_t len = 1;
  char *hsz;

  len += (path != NULL ? strlen (path) : 0);
  len += strlen (mcset_mc_basename);
  len += (ext != NULL ? strlen (ext) : 0);
  hsz = xmalloc (len);
  sprintf (hsz, "%s%s%s", (path != NULL ? path : ""), mcset_mc_basename,
    (ext != NULL ? ext : ""));
  if ((ret = fopen (hsz, "wb")) == NULL)
    fatal (_("can't create %s file ,%s' for output.\n"), (ext ? ext : "text"), hsz);
  free (hsz);
  return ret;
}