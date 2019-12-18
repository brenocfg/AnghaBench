#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ debug_dv; } ;
struct TYPE_5__ {scalar_t__ data_srlz; TYPE_1__* dependency; } ;
struct TYPE_4__ {scalar_t__ semantics; } ;

/* Variables and functions */
 scalar_t__ IA64_DVS_OTHER ; 
 scalar_t__ STATE_STOP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ md ; 
 int /*<<< orphan*/  print_dependency (char*,int) ; 
 TYPE_2__* regdeps ; 
 int regdepslen ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
data_serialization ()
{
  int i = 0;
  if (md.debug_dv)
    fprintf (stderr, "  Data serialization\n");
  while (i < regdepslen)
    {
      if (regdeps[i].data_srlz == STATE_STOP
	  /* Note: as of 991210, all "other" dependencies are cleared by a
	     data serialization.  This might change with new tables */
	  || (regdeps[i].dependency)->semantics == IA64_DVS_OTHER)
	{
	  print_dependency ("Removing", i);
	  regdeps[i] = regdeps[--regdepslen];
	}
      else
	++i;
    }
}