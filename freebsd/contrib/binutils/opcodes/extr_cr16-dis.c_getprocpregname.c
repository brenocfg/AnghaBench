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
struct TYPE_3__ {int image; char* name; } ;
typedef  TYPE_1__ reg_entry ;

/* Variables and functions */
 int NUMPREGPS ; 
 TYPE_1__ const* cr16_pregptab ; 

__attribute__((used)) static char *
getprocpregname (int index)
{
  const reg_entry *r;

  for (r = cr16_pregptab; r < cr16_pregptab + NUMPREGPS; r++)
    if (r->image == index)
      return r->name;

  return "ILLEGAL REGISTER";
}