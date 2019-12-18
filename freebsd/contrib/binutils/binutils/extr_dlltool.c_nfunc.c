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
struct TYPE_2__ {char* name; } ;
typedef  TYPE_1__ export_type ;

/* Variables and functions */
 scalar_t__ killat ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
nfunc (const void *a, const void *b)
{
  export_type *ap = *(export_type **) a;
  export_type *bp = *(export_type **) b;
  const char *an = ap->name;
  const char *bn = bp->name;

  if (killat)
    {
      an = (an[0] == '@') ? an + 1 : an;
      bn = (bn[0] == '@') ? bn + 1 : bn;
    }

  return (strcmp (an, bn));
}