#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* arch_info; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_4__ {unsigned long mach; } ;

/* Variables and functions */

unsigned long
bfd_get_mach (bfd *abfd)
{
  return abfd->arch_info->mach;
}