#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;
struct TYPE_6__ {TYPE_1__ l; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* top; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  const* StkId ;
typedef  TYPE_3__ CallInfo ;

/* Variables and functions */

__attribute__((used)) static int isinstack (CallInfo *ci, const TValue *o) {
  StkId p;
  for (p = ci->u.l.base; p < ci->top; p++)
    if (o == p) return 1;
  return 0;
}