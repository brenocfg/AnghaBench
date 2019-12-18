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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  CLASSTYPE_AS_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_class_hierarchy_r (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* type_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_class_hierarchy_1 (FILE *stream, int flags, tree t)
{
  fprintf (stream, "Class %s\n", type_as_string (t, TFF_PLAIN_IDENTIFIER));
  fprintf (stream, "   size=%lu align=%lu\n",
	   (unsigned long)(tree_low_cst (TYPE_SIZE (t), 0) / BITS_PER_UNIT),
	   (unsigned long)(TYPE_ALIGN (t) / BITS_PER_UNIT));
  fprintf (stream, "   base size=%lu base align=%lu\n",
	   (unsigned long)(tree_low_cst (TYPE_SIZE (CLASSTYPE_AS_BASE (t)), 0)
			   / BITS_PER_UNIT),
	   (unsigned long)(TYPE_ALIGN (CLASSTYPE_AS_BASE (t))
			   / BITS_PER_UNIT));
  dump_class_hierarchy_r (stream, flags, TYPE_BINFO (t), TYPE_BINFO (t), 0);
  fprintf (stream, "\n");
}