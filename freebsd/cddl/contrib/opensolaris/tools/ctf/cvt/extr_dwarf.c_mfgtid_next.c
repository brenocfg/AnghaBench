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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_3__ {int /*<<< orphan*/  dw_mfgtid_last; } ;
typedef  TYPE_1__ dwarf_t ;

/* Variables and functions */

__attribute__((used)) static tid_t
mfgtid_next(dwarf_t *dw)
{
	return (++dw->dw_mfgtid_last);
}