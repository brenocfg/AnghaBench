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
struct tekhex_asymbol_struct {int dummy; } ;
struct TYPE_3__ {int symcount; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */

__attribute__((used)) static long
tekhex_get_symtab_upper_bound (bfd *abfd)
{
  return (abfd->symcount + 1) * (sizeof (struct tekhex_asymbol_struct *));

}