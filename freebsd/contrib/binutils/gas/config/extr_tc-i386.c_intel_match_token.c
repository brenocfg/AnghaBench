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
struct TYPE_2__ {int code; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cur_token ; 
 int /*<<< orphan*/  intel_get_token () ; 

__attribute__((used)) static int
intel_match_token (int code)
{
  if (cur_token.code == code)
    {
      intel_get_token ();
      return 1;
    }
  else
    {
      as_bad (_("Unexpected token `%s'"), cur_token.str);
      return 0;
    }
}