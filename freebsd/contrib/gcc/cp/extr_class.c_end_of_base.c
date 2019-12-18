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

/* Variables and functions */
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ is_empty_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
end_of_base (tree binfo)
{
  tree size;

  if (is_empty_class (BINFO_TYPE (binfo)))
    /* An empty class has zero CLASSTYPE_SIZE_UNIT, but we need to
       allocate some space for it. It cannot have virtual bases, so
       TYPE_SIZE_UNIT is fine.  */
    size = TYPE_SIZE_UNIT (BINFO_TYPE (binfo));
  else
    size = CLASSTYPE_SIZE_UNIT (BINFO_TYPE (binfo));

  return size_binop (PLUS_EXPR, BINFO_OFFSET (binfo), size);
}