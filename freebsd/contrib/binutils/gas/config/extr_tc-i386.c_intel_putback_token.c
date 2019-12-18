#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  op_string; } ;
struct TYPE_4__ {scalar_t__ code; int /*<<< orphan*/ * str; int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 scalar_t__ T_NIL ; 
 TYPE_1__ cur_token ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__ intel_parser ; 
 TYPE_1__ prev_token ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_putback_token (void)
{
  if (cur_token.code != T_NIL)
    {
      intel_parser.op_string -= strlen (cur_token.str);
      free (cur_token.str);
    }
  cur_token = prev_token;

  /* Forget prev_token.  */
  prev_token.code = T_NIL;
  prev_token.reg = NULL;
  prev_token.str = NULL;
}