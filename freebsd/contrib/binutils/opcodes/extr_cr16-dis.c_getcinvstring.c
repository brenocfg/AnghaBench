#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ostr; int /*<<< orphan*/  istr; } ;
typedef  TYPE_1__ cinv_entry ;

/* Variables and functions */
 char* ILLEGAL ; 
 int NUMCINVS ; 
 TYPE_1__ const* cr16_cinvs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
getcinvstring (char *str)
{
  const cinv_entry *cinv;

  for (cinv = cr16_cinvs; cinv < (cr16_cinvs + NUMCINVS); cinv++)
    if (strcmp (cinv->istr, str) == 0)
      return cinv->ostr;

  return ILLEGAL;
}