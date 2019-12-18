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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* ar_replace ) (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ bin_dummy_emulation ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 

bfd_boolean
ar_emul_replace (bfd **after_bfd, char *file_name, bfd_boolean verbose)
{
  if (bin_dummy_emulation.ar_replace)
    return bin_dummy_emulation.ar_replace (after_bfd, file_name, verbose);

  return FALSE;
}