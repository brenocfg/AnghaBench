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
struct pex_obj {int dummy; } ;

/* Variables and functions */
 struct pex_obj* collect_execute (char const*,char**,char const*,char const*) ; 
 int collect_wait (char const*,struct pex_obj*) ; 

__attribute__((used)) static int
tlink_execute (const char *prog, char **argv, const char *outname,
	       const char *errname)
{
  struct pex_obj *pex;

  pex = collect_execute (prog, argv, outname, errname);
  return collect_wait (prog, pex);
}