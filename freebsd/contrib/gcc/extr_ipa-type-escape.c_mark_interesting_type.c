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
typedef  int /*<<< orphan*/  tree ;
typedef  enum escape_t { ____Placeholder_escape_t } escape_t ;

/* Variables and functions */
 int EXPOSED_PARAMETER ; 
 int FULL_ESCAPE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
mark_interesting_type (tree type, enum escape_t escape_status)
{
  if (!type) return;
  if (ipa_type_escape_star_count_of_interesting_type (type) >= 0)
    {
      if ((escape_status == EXPOSED_PARAMETER)
	  && POINTER_TYPE_P (type))
	/* EXPOSED_PARAMETERs are only structs or unions are passed by
	   value.  Anything passed by reference to an external
	   function fully exposes the type.  */
	mark_type (type, FULL_ESCAPE);
      else
	mark_type (type, escape_status);
    }
}