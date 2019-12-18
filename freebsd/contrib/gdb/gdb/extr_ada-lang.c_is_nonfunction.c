#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_FUNC ; 

__attribute__((used)) static int
is_nonfunction (struct symbol *syms[], int n)
{
  int i;

  for (i = 0; i < n; i += 1)
    if (TYPE_CODE (SYMBOL_TYPE (syms[i])) != TYPE_CODE_FUNC
	&& TYPE_CODE (SYMBOL_TYPE (syms[i])) != TYPE_CODE_ENUM)
      return 1;

  return 0;
}