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
 int /*<<< orphan*/  TDI_class ; 
 int /*<<< orphan*/ * dump_begin (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dump_class_hierarchy_1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_class_hierarchy (tree t)
{
  int flags;
  FILE *stream = dump_begin (TDI_class, &flags);

  if (stream)
    {
      dump_class_hierarchy_1 (stream, flags, t);
      dump_end (TDI_class, stream);
    }
}