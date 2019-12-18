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
struct TYPE_3__ {int /*<<< orphan*/ * ilcs_common; } ;
typedef  TYPE_1__ ILCS_SERVICE_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */

ILCS_COMMON_T *ilcs_get_common(ILCS_SERVICE_T *st)
{
   return st->ilcs_common;
}