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
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  generic_link_add_symbols (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_generic_link_add_symbols_collect (bfd *abfd, struct bfd_link_info *info)
{
  return generic_link_add_symbols (abfd, info, TRUE);
}