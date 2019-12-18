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
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {scalar_t__ dll; } ;

/* Variables and functions */
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 scalar_t__ obj_pe (int /*<<< orphan*/ *) ; 
 TYPE_1__* pe_data (int /*<<< orphan*/ *) ; 

bfd_boolean
pe_bfd_is_dll (bfd *abfd)
{
  return (bfd_get_format (abfd) == bfd_object
          && obj_pe (abfd)
          && pe_data (abfd)->dll);
}