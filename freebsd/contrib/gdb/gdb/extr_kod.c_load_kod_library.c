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
 int /*<<< orphan*/  cisco_kod_close ; 
 int /*<<< orphan*/  cisco_kod_open ; 
 int /*<<< orphan*/  cisco_kod_request ; 
 int /*<<< orphan*/  ecos_kod_close ; 
 int /*<<< orphan*/  ecos_kod_open ; 
 int /*<<< orphan*/  ecos_kod_request ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_kod_close ; 
 int /*<<< orphan*/  gdb_kod_open ; 
 int /*<<< orphan*/  gdb_kod_request ; 
 int /*<<< orphan*/  operating_system ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
load_kod_library (char *lib)
{
#if 0
  /* FIXME: Don't have the eCos code here.  */
  if (! strcmp (lib, "ecos"))
    {
      gdb_kod_open = ecos_kod_open;
      gdb_kod_request = ecos_kod_request;
      gdb_kod_close = ecos_kod_close;
    }
  else
#endif /* 0 */
   if (! strcmp (lib, "cisco"))
    {
      gdb_kod_open = cisco_kod_open;
      gdb_kod_request = cisco_kod_request;
      gdb_kod_close = cisco_kod_close;
    }
  else
    error ("Unknown operating system: %s\n", operating_system);
}