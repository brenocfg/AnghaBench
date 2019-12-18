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
struct TYPE_2__ {int /*<<< orphan*/  preferred_amq_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_1__ gopt ; 

__attribute__((used)) static int
gopt_preferred_amq_port(const char *val)
{
  gopt.preferred_amq_port = atoi(val);

  /*
   * No need to check value: preferred_amq_port is an unsigned short and 0
   * is a valid number, meaning "any port".
   */
  return 0;			/* all is OK */
}