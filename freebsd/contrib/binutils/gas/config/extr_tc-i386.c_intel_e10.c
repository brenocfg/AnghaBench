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
struct TYPE_2__ {char code; } ;

/* Variables and functions */
 TYPE_1__ cur_token ; 
 int /*<<< orphan*/  intel_bracket_expr () ; 
 int /*<<< orphan*/  intel_e11 () ; 

__attribute__((used)) static int
intel_e10 (void)
{
  if (!intel_e11 ())
    return 0;

  while (cur_token.code == '[')
    {
      if (!intel_bracket_expr ())
	return 0;
    }

  return 1;
}