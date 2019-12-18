#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int DF_EQUIV_NOTES ; 
 int DF_HARD_REGS ; 
 int /*<<< orphan*/  DF_UD_CHAIN ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biv_eq ; 
 int /*<<< orphan*/  biv_hash ; 
 int /*<<< orphan*/  bivs ; 
 int /*<<< orphan*/  clear_iv_info () ; 
 struct loop* current_loop ; 
 int /*<<< orphan*/ * df ; 
 int /*<<< orphan*/  df_analyze (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  df_chain_add_problem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * df_init (int) ; 
 int /*<<< orphan*/  df_set_blocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_loop_body_in_dom_order (struct loop*) ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__**)) ; 

void
iv_analysis_loop_init (struct loop *loop)
{
  basic_block *body = get_loop_body_in_dom_order (loop), bb;
  bitmap blocks = BITMAP_ALLOC (NULL);
  unsigned i;
  bool first_time = (df == NULL);

  current_loop = loop;

  /* Clear the information from the analysis of the previous loop.  */
  if (first_time)
    {
      df = df_init (DF_HARD_REGS | DF_EQUIV_NOTES);
      df_chain_add_problem (df, DF_UD_CHAIN);
      bivs = htab_create (10, biv_hash, biv_eq, free);
    }
  else
    clear_iv_info ();

  for (i = 0; i < loop->num_nodes; i++)
    {
      bb = body[i];
      bitmap_set_bit (blocks, bb->index);
    }
  df_set_blocks (df, blocks);
  df_analyze (df); 
  BITMAP_FREE (blocks);
  free (body);
}