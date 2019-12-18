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
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const BINFO_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ DEBUG_MANGLE ; 
 char* finish_mangling (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  get_identifier_nocopy (char const*) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_integer_cst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/  const) ; 

tree
mangle_ctor_vtbl_for_type (const tree type, const tree binfo)
{
  const char *result;

  start_mangling (type, /*ident_p=*/true);

  write_string ("_Z");
  write_string ("TC");
  write_type (type);
  write_integer_cst (BINFO_OFFSET (binfo));
  write_char ('_');
  write_type (BINFO_TYPE (binfo));

  result = finish_mangling (/*warn=*/false);
  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_ctor_vtbl_for_type = %s\n\n", result);
  return get_identifier_nocopy (result);
}