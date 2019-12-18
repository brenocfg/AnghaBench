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
struct z_candidate {int num_convs; int viable; int /*<<< orphan*/  fn; TYPE_1__** convs; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (char*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
print_z_candidate (const char *msgstr, struct z_candidate *candidate)
{
  if (TREE_CODE (candidate->fn) == IDENTIFIER_NODE)
    {
      if (candidate->num_convs == 3)
	inform ("%s %D(%T, %T, %T) <built-in>", msgstr, candidate->fn,
		candidate->convs[0]->type,
		candidate->convs[1]->type,
		candidate->convs[2]->type);
      else if (candidate->num_convs == 2)
	inform ("%s %D(%T, %T) <built-in>", msgstr, candidate->fn,
		candidate->convs[0]->type,
		candidate->convs[1]->type);
      else
	inform ("%s %D(%T) <built-in>", msgstr, candidate->fn,
		candidate->convs[0]->type);
    }
  else if (TYPE_P (candidate->fn))
    inform ("%s %T <conversion>", msgstr, candidate->fn);
  else if (candidate->viable == -1)
    inform ("%s %+#D <near match>", msgstr, candidate->fn);
  else
    inform ("%s %+#D", msgstr, candidate->fn);
}