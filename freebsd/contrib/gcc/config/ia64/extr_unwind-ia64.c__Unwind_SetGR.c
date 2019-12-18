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
struct _Unwind_Context {void** eh_data; void* gp; } ;
typedef  void* _Unwind_Word ;

/* Variables and functions */
 int /*<<< orphan*/  unw_access_gr (struct _Unwind_Context*,int,void**,char*,int) ; 

void
_Unwind_SetGR (struct _Unwind_Context *context, int index, _Unwind_Word val)
{
  char nat = 0;

  if (index == 1)
    context->gp = val;
  else if (index >= 15 && index <= 18)
    context->eh_data[index - 15] = val;
  else
    unw_access_gr (context, index, &val, &nat, 1);
}