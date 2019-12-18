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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ DEBUG_MANGLE ; 
 char* finish_mangling (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/  const) ; 

const char *
mangle_type_string (const tree type)
{
  const char *result;

  start_mangling (type, /*ident_p=*/false);
  write_type (type);
  result = finish_mangling (/*warn=*/false);
  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_type_string = '%s'\n\n", result);
  return result;
}