#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  def; int /*<<< orphan*/  actual; } ;
typedef  TYPE_1__ formal_entry ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  sb_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
del_formal (formal_entry *formal)
{
  sb_kill (&formal->actual);
  sb_kill (&formal->def);
  sb_kill (&formal->name);
  free (formal);
}