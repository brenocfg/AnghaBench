#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* constraint_graph_t ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_3__ {unsigned int size; int /*<<< orphan*/ * preds; int /*<<< orphan*/ * implicit_preds; scalar_t__* succs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (scalar_t__) ; 
 unsigned int FIRST_REF_NODE ; 
 unsigned int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_range (scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  bitmap_obstack_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  predbitmap_obstack ; 
 int /*<<< orphan*/  varinfo_t ; 
 int /*<<< orphan*/  varmap ; 
 scalar_t__* xrealloc (scalar_t__*,int) ; 

__attribute__((used)) static void
remove_preds_and_fake_succs (constraint_graph_t graph)
{
  unsigned int i;

  /* Clear the implicit ref and address nodes from the successor
     lists.  */
  for (i = 0; i < FIRST_REF_NODE; i++)
    {
      if (graph->succs[i])
	bitmap_clear_range (graph->succs[i], FIRST_REF_NODE,
			    FIRST_REF_NODE * 2);
    }

  /* Free the successor list for the non-ref nodes.  */
  for (i = FIRST_REF_NODE; i < graph->size; i++)
    {
      if (graph->succs[i])
	BITMAP_FREE (graph->succs[i]);
    }

  /* Now reallocate the size of the successor list as, and blow away
     the predecessor bitmaps.  */
  graph->size = VEC_length (varinfo_t, varmap);
  graph->succs = xrealloc (graph->succs, graph->size * sizeof (bitmap));

  free (graph->implicit_preds);
  graph->implicit_preds = NULL;
  free (graph->preds);
  graph->preds = NULL;
  bitmap_obstack_release (&predbitmap_obstack);
}