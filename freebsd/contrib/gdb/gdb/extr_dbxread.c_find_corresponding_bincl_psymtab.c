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
struct partial_symtab {int dummy; } ;
struct header_file_location {int instance; struct partial_symtab* pst; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct header_file_location* bincl_list ; 
 struct header_file_location* next_bincl ; 
 int /*<<< orphan*/  repeated_header_complaint (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symnum ; 

__attribute__((used)) static struct partial_symtab *
find_corresponding_bincl_psymtab (char *name, int instance)
{
  struct header_file_location *bincl;

  for (bincl = bincl_list; bincl < next_bincl; bincl++)
    if (bincl->instance == instance
	&& strcmp (name, bincl->name) == 0)
      return bincl->pst;

  repeated_header_complaint (name, symnum);
  return (struct partial_symtab *) 0;
}