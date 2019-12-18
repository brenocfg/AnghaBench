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
 char* base_name (char const*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char const *
expand_name (char *name, bool is_dir, char const *other_name)
{
  if (strcmp (name, "-") == 0)
    fatal ("cannot interactively merge standard input");
  if (! is_dir)
    return name;
  else
    {
      /* Yield NAME/BASE, where BASE is OTHER_NAME's basename.  */
      char const *base = base_name (other_name);
      size_t namelen = strlen (name), baselen = strlen (base);
      bool insert_slash = *base_name (name) && name[namelen - 1] != '/';
      char *r = xmalloc (namelen + insert_slash + baselen + 1);
      memcpy (r, name, namelen);
      r[namelen] = '/';
      memcpy (r + namelen + insert_slash, base, baselen + 1);
      return r;
    }
}