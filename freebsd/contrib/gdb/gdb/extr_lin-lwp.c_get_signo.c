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
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  signo ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
get_signo (const char *name)
{
  struct minimal_symbol *ms;
  int signo;

  ms = lookup_minimal_symbol (name, NULL, NULL);
  if (ms == NULL)
    return 0;

  if (target_read_memory (SYMBOL_VALUE_ADDRESS (ms), (char *) &signo,
			  sizeof (signo)) != 0)
    return 0;

  return signo;
}