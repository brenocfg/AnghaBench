#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct unnamed_section {int dummy; } ;
struct TYPE_6__ {unsigned int flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  callback; TYPE_1__ common; } ;
struct TYPE_8__ {TYPE_2__ noswitch; } ;
typedef  TYPE_3__ section ;
typedef  int /*<<< orphan*/  noswitch_section_callback ;

/* Variables and functions */
 unsigned int SECTION_NOSWITCH ; 
 TYPE_3__* ggc_alloc (int) ; 

__attribute__((used)) static section *
get_noswitch_section (unsigned int flags, noswitch_section_callback callback)
{
  section *sect;

  sect = ggc_alloc (sizeof (struct unnamed_section));
  sect->noswitch.common.flags = flags | SECTION_NOSWITCH;
  sect->noswitch.callback = callback;

  return sect;
}