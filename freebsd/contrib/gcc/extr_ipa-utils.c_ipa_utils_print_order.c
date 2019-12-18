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
struct cgraph_node {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_cgraph_node (int /*<<< orphan*/ ,struct cgraph_node*) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void 
ipa_utils_print_order (FILE* out, 
		       const char * note, 
		       struct cgraph_node** order, 
		       int count) 
{
  int i;
  fprintf (out, "\n\n ordered call graph: %s\n", note);
  
  for (i = count - 1; i >= 0; i--)
    dump_cgraph_node(dump_file, order[i]);
  fprintf (out, "\n");
  fflush(out);
}