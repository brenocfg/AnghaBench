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
struct TYPE_3__ {int entry; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ trap_entry ;

/* Variables and functions */
 int NUMTRAPS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ atoi (char*) ; 
 TYPE_1__ const* cr16_traps ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gettrap (char *s)
{
  const trap_entry *trap;

  for (trap = cr16_traps; trap < (cr16_traps + NUMTRAPS); trap++)
    if (strcasecmp (trap->name, s) == 0)
      return trap->entry;

  /* To make compatable with CR16 4.1 tools, the below 3-lines of
   * code added. Refer: Development Tracker item #123 */
  for (trap = cr16_traps; trap < (cr16_traps + NUMTRAPS); trap++)
    if (trap->entry  == (unsigned int) atoi (s))
      return trap->entry;

  as_bad (_("Unknown exception: `%s'"), s);
  return 0;
}