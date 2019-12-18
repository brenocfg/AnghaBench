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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFM_MOUNT_TYPE_AUTOFS ; 
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  amd_use_autofs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_mount_type(const char *val)
{
  if (STREQ(val, "autofs")) {
#ifdef HAVE_FS_AUTOFS
    gopt.flags |= CFM_MOUNT_TYPE_AUTOFS;
    amd_use_autofs++;
    return 0;
#else /* not HAVE_FS_AUTOFS */
    fprintf(stderr, "conf: no autofs support available\n");
    return 1;
#endif /* not HAVE_FS_AUTOFS */
  } else if (STREQ(val, "nfs")) {
    gopt.flags &= ~CFM_MOUNT_TYPE_AUTOFS;
    return 0;
  }

  fprintf(stderr, "conf: unknown value to mount_type \"%s\"\n", val);
  return 1;			/* unknown value */
}