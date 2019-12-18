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
struct TYPE_3__ {int /*<<< orphan*/  ps_b; } ;
typedef  TYPE_1__ PE_Scn ;

/* Variables and functions */
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_SORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PE_SecBuf ; 
 int /*<<< orphan*/  cmp_sb ; 
 int /*<<< orphan*/  sb_next ; 

__attribute__((used)) static void
sort_buffers(PE_Scn *ps)
{

	if (STAILQ_EMPTY(&ps->ps_b))
		return;

	STAILQ_SORT(&ps->ps_b, _PE_SecBuf, sb_next, cmp_sb);
}