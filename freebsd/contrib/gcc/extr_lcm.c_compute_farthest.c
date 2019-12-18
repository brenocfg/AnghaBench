#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct edge_list {int dummy; } ;
typedef  int /*<<< orphan*/  sbitmap ;
typedef  TYPE_1__* basic_block ;
struct TYPE_6__ {size_t index; } ;

/* Variables and functions */
 TYPE_1__* ENTRY_BLOCK_PTR ; 
 TYPE_1__* EXIT_BLOCK_PTR ; 
 TYPE_1__* INDEX_EDGE_PRED_BB (struct edge_list*,int) ; 
 TYPE_1__* INDEX_EDGE_SUCC_BB (struct edge_list*,int) ; 
 int NUM_EDGES (struct edge_list*) ; 
 int /*<<< orphan*/  sbitmap_a_and_b_or_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_alloc (int) ; 
 int /*<<< orphan*/  sbitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compute_farthest (struct edge_list *edge_list, int n_exprs,
		  sbitmap *st_avout, sbitmap *st_avin, sbitmap *st_antin,
		  sbitmap *kill, sbitmap *farthest)
{
  sbitmap difference, temp_bitmap;
  int x, num_edges;
  basic_block pred, succ;

  num_edges = NUM_EDGES (edge_list);

  difference = sbitmap_alloc (n_exprs);
  temp_bitmap = sbitmap_alloc (n_exprs);

  for (x = 0; x < num_edges; x++)
    {
      pred = INDEX_EDGE_PRED_BB (edge_list, x);
      succ = INDEX_EDGE_SUCC_BB (edge_list, x);
      if (succ == EXIT_BLOCK_PTR)
	sbitmap_copy (farthest[x], st_avout[pred->index]);
      else
	{
	  if (pred == ENTRY_BLOCK_PTR)
	    sbitmap_zero (farthest[x]);
	  else
	    {
	      sbitmap_difference (difference, st_avout[pred->index],
				  st_antin[succ->index]);
	      sbitmap_not (temp_bitmap, st_avin[succ->index]);
	      sbitmap_a_and_b_or_c (farthest[x], difference,
				    kill[succ->index], temp_bitmap);
	    }
	}
    }

  sbitmap_free (temp_bitmap);
  sbitmap_free (difference);
}