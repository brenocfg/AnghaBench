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
struct gdbarch_info {int /*<<< orphan*/ * abfd; } ;
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct gdbarch* current_gdbarch ; 
 struct gdbarch* gdbarch_find_by_info (struct gdbarch_info) ; 
 int /*<<< orphan*/  gdbarch_info_init (struct gdbarch_info*) ; 

struct gdbarch *
gdbarch_from_bfd (bfd *abfd)
{
  struct gdbarch *old_gdbarch = current_gdbarch;
  struct gdbarch *new_gdbarch;
  struct gdbarch_info info;

  gdbarch_info_init (&info);
  info.abfd = abfd;
  return gdbarch_find_by_info (info);
}