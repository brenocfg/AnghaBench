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
struct TYPE_2__ {int inpragma; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCC_BAD (char*) ; 
 int /*<<< orphan*/  VEC_safe_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VISIBILITY_DEFAULT ; 
 int /*<<< orphan*/  VISIBILITY_HIDDEN ; 
 int /*<<< orphan*/  VISIBILITY_INTERNAL ; 
 int /*<<< orphan*/  VISIBILITY_PROTECTED ; 
 int /*<<< orphan*/  default_visibility ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  visibility ; 
 TYPE_1__ visibility_options ; 
 int /*<<< orphan*/  visstack ; 

void
push_visibility (const char *str)
{
  VEC_safe_push (visibility, heap, visstack,
		 default_visibility);
  if (!strcmp (str, "default"))
    default_visibility = VISIBILITY_DEFAULT;
  else if (!strcmp (str, "internal"))
    default_visibility = VISIBILITY_INTERNAL;
  else if (!strcmp (str, "hidden"))
    default_visibility = VISIBILITY_HIDDEN;
  else if (!strcmp (str, "protected"))
    default_visibility = VISIBILITY_PROTECTED;
  else
    GCC_BAD ("#pragma GCC visibility push() must specify default, internal, hidden or protected");
  visibility_options.inpragma = 1;
}