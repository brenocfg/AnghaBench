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
typedef  int /*<<< orphan*/  bfd_error_handler_type ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_error_handler ; 

bfd_error_handler_type
bfd_set_error_handler (bfd_error_handler_type pnew)
{
  bfd_error_handler_type pold;

  pold = _bfd_error_handler;
  _bfd_error_handler = pnew;
  return pold;
}