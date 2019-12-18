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
struct TYPE_2__ {int /*<<< orphan*/  (* ar_usage ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ bin_dummy_emulation ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
ar_emul_usage (FILE *fp)
{
  if (bin_dummy_emulation.ar_usage)
    bin_dummy_emulation.ar_usage (fp);
}