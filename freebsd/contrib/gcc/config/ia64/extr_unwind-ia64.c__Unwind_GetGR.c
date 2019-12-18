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
struct _Unwind_Context {int /*<<< orphan*/ * eh_data; int /*<<< orphan*/  gp; } ;
typedef  int /*<<< orphan*/  _Unwind_Word ;

/* Variables and functions */
 int /*<<< orphan*/  unw_access_gr (struct _Unwind_Context*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

_Unwind_Word
_Unwind_GetGR (struct _Unwind_Context *context, int index)
{
  _Unwind_Word ret;
  char nat;

  if (index == 1)
    return context->gp;
  else if (index >= 15 && index <= 18)
    return context->eh_data[index - 15];
  else
    unw_access_gr (context, index, &ret, &nat, 0);

  return ret;
}