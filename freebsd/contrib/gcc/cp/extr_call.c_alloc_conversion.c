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
typedef  int /*<<< orphan*/  conversion_kind ;
struct TYPE_3__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 scalar_t__ conversion_obstack_alloc (int) ; 

__attribute__((used)) static conversion *
alloc_conversion (conversion_kind kind)
{
  conversion *c;
  c = (conversion *) conversion_obstack_alloc (sizeof (conversion));
  c->kind = kind;
  return c;
}