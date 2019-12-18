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
struct TYPE_2__ {int /*<<< orphan*/  prev_sp; } ;
typedef  TYPE_1__ phase1_vrs ;
typedef  int /*<<< orphan*/  _Unwind_Word ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */

_Unwind_Word
_Unwind_GetCFA (_Unwind_Context *context)
{
  return ((phase1_vrs *) context)->prev_sp;
}