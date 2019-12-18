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
typedef  int /*<<< orphan*/  tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  fix_small_cpu_struct (int /*<<< orphan*/ *,size_t) ; 

void
cvt_fixups(tdata_t *td, size_t ptrsize)
{
	fix_small_cpu_struct(td, ptrsize);
}