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
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_2__ {int type; int desc; int /*<<< orphan*/ * string; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t SAVE_STABS_COUNT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* saved_stabs ; 
 size_t saved_stabs_index ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

__attribute__((used)) static void
save_stab (int type, int desc, bfd_vma value, const char *string)
{
  if (saved_stabs[saved_stabs_index].string != NULL)
    free (saved_stabs[saved_stabs_index].string);
  saved_stabs[saved_stabs_index].type = type;
  saved_stabs[saved_stabs_index].desc = desc;
  saved_stabs[saved_stabs_index].value = value;
  saved_stabs[saved_stabs_index].string = xstrdup (string);
  saved_stabs_index = (saved_stabs_index + 1) % SAVE_STABS_COUNT;
}