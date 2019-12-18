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
struct TYPE_2__ {unsigned long line; } ;
union sltentry {TYPE_1__ snorm; } ;
struct objfile {int dummy; } ;
typedef  int /*<<< orphan*/  sltpointer ;

/* Variables and functions */
 union sltentry* hpread_get_slt (int /*<<< orphan*/ ,struct objfile*) ; 

__attribute__((used)) static unsigned long
hpread_get_line (sltpointer index, struct objfile *objfile)
{
  union sltentry *sl_bufp;

  sl_bufp = hpread_get_slt (index, objfile);
  return sl_bufp->snorm.line;
}