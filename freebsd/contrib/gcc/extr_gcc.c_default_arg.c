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
struct TYPE_2__ {int len; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 TYPE_1__* mdswitches ; 
 int n_mdswitches ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
default_arg (const char *p, int len)
{
  int i;

  for (i = 0; i < n_mdswitches; i++)
    if (len == mdswitches[i].len && ! strncmp (p, mdswitches[i].str, len))
      return 1;

  return 0;
}