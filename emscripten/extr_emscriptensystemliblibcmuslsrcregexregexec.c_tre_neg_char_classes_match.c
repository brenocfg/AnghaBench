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
typedef  scalar_t__ tre_ctype_t ;
typedef  int /*<<< orphan*/  tre_cint_t ;

/* Variables and functions */
 scalar_t__ tre_isctype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tre_tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tre_toupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tre_neg_char_classes_match(tre_ctype_t *classes, tre_cint_t wc, int icase)
{
  while (*classes != (tre_ctype_t)0)
    if ((!icase && tre_isctype(wc, *classes))
	|| (icase && (tre_isctype(tre_toupper(wc), *classes)
		      || tre_isctype(tre_tolower(wc), *classes))))
      return 1; /* Match. */
    else
      classes++;
  return 0; /* No match. */
}