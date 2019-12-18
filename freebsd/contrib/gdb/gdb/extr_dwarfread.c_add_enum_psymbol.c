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
struct objfile {int /*<<< orphan*/  static_psymbols; } ;
struct dieinfo {char* at_element_list; scalar_t__ short_element_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_element_list ; 
 int /*<<< orphan*/  AT_short_element_list ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 int /*<<< orphan*/  LOC_CONST ; 
 int /*<<< orphan*/  TARGET_FT_LONG_SIZE (struct objfile*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  add_psymbol_to_list (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 int attribute_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cu_language ; 
 scalar_t__ strlen (char*) ; 
 unsigned short target_to_host (char*,int,int /*<<< orphan*/ ,struct objfile*) ; 

__attribute__((used)) static void
add_enum_psymbol (struct dieinfo *dip, struct objfile *objfile)
{
  char *scan;
  char *listend;
  unsigned short blocksz;
  int nbytes;

  scan = dip->at_element_list;
  if (scan != NULL)
    {
      if (dip->short_element_list)
	{
	  nbytes = attribute_size (AT_short_element_list);
	}
      else
	{
	  nbytes = attribute_size (AT_element_list);
	}
      blocksz = target_to_host (scan, nbytes, GET_UNSIGNED, objfile);
      scan += nbytes;
      listend = scan + blocksz;
      while (scan < listend)
	{
	  scan += TARGET_FT_LONG_SIZE (objfile);
	  add_psymbol_to_list (scan, strlen (scan), VAR_DOMAIN, LOC_CONST,
			       &objfile->static_psymbols, 0, 0, cu_language,
			       objfile);
	  scan += strlen (scan) + 1;
	}
    }
}