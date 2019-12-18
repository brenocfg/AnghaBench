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
struct core_fns {scalar_t__ core_flavour; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 

int
default_core_sniffer (struct core_fns *our_fns, bfd *abfd)
{
  int result;

  result = (bfd_get_flavour (abfd) == our_fns -> core_flavour);
  return (result);
}