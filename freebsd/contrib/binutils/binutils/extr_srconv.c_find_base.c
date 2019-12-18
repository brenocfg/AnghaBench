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
struct coff_sfile {TYPE_1__* section; } ;
struct coff_section {size_t number; } ;
struct TYPE_2__ {int low; } ;

/* Variables and functions */

__attribute__((used)) static int
find_base (struct coff_sfile *sfile, struct coff_section *section)
{
  return sfile->section[section->number].low;
}