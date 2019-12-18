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
 int /*<<< orphan*/  DLL_IMPORT_PREFIX ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
i386_pe_dllimport_name_p (const char *symbol)
{
  return (strncmp (DLL_IMPORT_PREFIX, symbol,
		   strlen (DLL_IMPORT_PREFIX)) == 0);
}