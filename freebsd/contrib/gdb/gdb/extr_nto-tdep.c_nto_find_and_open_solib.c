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
struct TYPE_2__ {char* arch_name; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int PATH_MAX ; 
 TYPE_1__* TARGET_ARCHITECTURE ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 char* alloca (int) ; 
 char* nto_target () ; 
 int openp (char*,int,char*,unsigned int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

int
nto_find_and_open_solib (char *solib, unsigned o_flags, char **temp_pathname)
{
  char *buf, arch_path[PATH_MAX], *nto_root, *endian;
  const char *arch;
  char *path_fmt = "%s/lib:%s/usr/lib:%s/usr/photon/lib\
:%s/usr/photon/dll:%s/lib/dll";

  nto_root = nto_target ();
  if (strcmp (TARGET_ARCHITECTURE->arch_name, "i386") == 0)
    {
      arch = "x86";
      endian = "";
    }
  else if (strcmp (TARGET_ARCHITECTURE->arch_name, "rs6000") == 0
	   || strcmp (TARGET_ARCHITECTURE->arch_name, "powerpc") == 0)
    {
      arch = "ppc";
      endian = "be";
    }
  else
    {
      arch = TARGET_ARCHITECTURE->arch_name;
      endian = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? "be" : "le";
    }

  sprintf (arch_path, "%s/%s%s", nto_root, arch, endian);

  buf = alloca (strlen (path_fmt) + strlen (arch_path) * 5 + 1);
  sprintf (buf, path_fmt, arch_path, arch_path, arch_path, arch_path,
	   arch_path);

  return openp (buf, 1, solib, o_flags, 0, temp_pathname);
}