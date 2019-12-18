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
struct type {int dummy; } ;
typedef  int DIE_REF ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  FT_INTEGER ; 
 struct type* alloc_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_die_ref_complaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_objfile ; 
 int dbroff ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int numutypes ; 
 int /*<<< orphan*/  symfile_complaints ; 
 struct type** utypes ; 

__attribute__((used)) static struct type *
alloc_utype (DIE_REF die_ref, struct type *utypep)
{
  struct type **typep;
  int utypeidx;

  utypeidx = (die_ref - dbroff) / 4;
  typep = utypes + utypeidx;
  if ((utypeidx < 0) || (utypeidx >= numutypes))
    {
      utypep = dwarf_fundamental_type (current_objfile, FT_INTEGER);
      bad_die_ref_complaint (DIE_ID, DIE_NAME, die_ref);
    }
  else if (*typep != NULL)
    {
      utypep = *typep;
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", internal error: duplicate user type allocation",
		 DIE_ID, DIE_NAME);
    }
  else
    {
      if (utypep == NULL)
	{
	  utypep = alloc_type (current_objfile);
	}
      *typep = utypep;
    }
  return (utypep);
}