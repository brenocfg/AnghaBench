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
 int TDF_SLIM ; 
 int /*<<< orphan*/  TDI_class ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 int /*<<< orphan*/  dump_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dump_begin (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* type_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_vtt (tree t, tree vtt)
{
  int flags;
  FILE *stream = dump_begin (TDI_class, &flags);

  if (!stream)
    return;

  if (!(flags & TDF_SLIM))
    {
      fprintf (stream, "VTT for %s\n",
	       type_as_string (t, TFF_PLAIN_IDENTIFIER));
      dump_array (stream, vtt);
      fprintf (stream, "\n");
    }

  dump_end (TDI_class, stream);
}