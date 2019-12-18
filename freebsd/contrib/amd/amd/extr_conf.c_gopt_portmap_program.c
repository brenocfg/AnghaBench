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
struct TYPE_2__ {scalar_t__ portmap_program; } ;

/* Variables and functions */
 scalar_t__ AMQ_PROGRAM ; 
 scalar_t__ atol (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  set_amd_program_number (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_portmap_program(const char *val)
{
  gopt.portmap_program = atol(val);
  /*
   * allow alternate program numbers to be no more than 10 offset from
   * official amd program number (300019).
   */
  if (gopt.portmap_program < AMQ_PROGRAM ||
      gopt.portmap_program > AMQ_PROGRAM + 10) {
    gopt.portmap_program = AMQ_PROGRAM;
    set_amd_program_number(gopt.portmap_program);
    fprintf(stderr, "conf: illegal amd program number \"%s\"\n", val);
    return 1;
  }

  set_amd_program_number(gopt.portmap_program);
  return 0;			/* all is OK */
}