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
struct edge_list {int dummy; } ;
typedef  int /*<<< orphan*/  sbitmap ;

/* Variables and functions */
 int NUM_EDGES (struct edge_list*) ; 
 int /*<<< orphan*/  compute_antinout_edge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_available (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_farthest (struct edge_list*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_nearerout (struct edge_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_rev_insert_delete (struct edge_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct edge_list* create_edge_list () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_sbitmap_vector (scalar_t__,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int last_basic_block ; 
 int /*<<< orphan*/  print_edge_list (scalar_t__,struct edge_list*) ; 
 int /*<<< orphan*/ * sbitmap_vector_alloc (int,int) ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_vector_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verify_edge_list (scalar_t__,struct edge_list*) ; 

struct edge_list *
pre_edge_rev_lcm (int n_exprs, sbitmap *transp,
		  sbitmap *st_avloc, sbitmap *st_antloc, sbitmap *kill,
		  sbitmap **insert, sbitmap **delete)
{
  sbitmap *st_antin, *st_antout;
  sbitmap *st_avout, *st_avin, *farthest;
  sbitmap *nearer, *nearerout;
  struct edge_list *edge_list;
  int num_edges;

  edge_list = create_edge_list ();
  num_edges = NUM_EDGES (edge_list);

  st_antin = sbitmap_vector_alloc (last_basic_block, n_exprs);
  st_antout = sbitmap_vector_alloc (last_basic_block, n_exprs);
  sbitmap_vector_zero (st_antin, last_basic_block);
  sbitmap_vector_zero (st_antout, last_basic_block);
  compute_antinout_edge (st_antloc, transp, st_antin, st_antout);

  /* Compute global anticipatability.  */
  st_avout = sbitmap_vector_alloc (last_basic_block, n_exprs);
  st_avin = sbitmap_vector_alloc (last_basic_block, n_exprs);
  compute_available (st_avloc, kill, st_avout, st_avin);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      fprintf (dump_file, "Edge List:\n");
      verify_edge_list (dump_file, edge_list);
      print_edge_list (dump_file, edge_list);
      dump_sbitmap_vector (dump_file, "transp", "", transp, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_avloc", "", st_avloc, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_antloc", "", st_antloc, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_antin", "", st_antin, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_antout", "", st_antout, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_kill", "", kill, last_basic_block);
    }
#endif

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      dump_sbitmap_vector (dump_file, "st_avout", "", st_avout, last_basic_block);
      dump_sbitmap_vector (dump_file, "st_avin", "", st_avin, last_basic_block);
    }
#endif

  /* Compute farthestness.  */
  farthest = sbitmap_vector_alloc (num_edges, n_exprs);
  compute_farthest (edge_list, n_exprs, st_avout, st_avin, st_antin,
		    kill, farthest);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    dump_sbitmap_vector (dump_file, "farthest", "", farthest, num_edges);
#endif

  sbitmap_vector_free (st_antin);
  sbitmap_vector_free (st_antout);

  sbitmap_vector_free (st_avin);
  sbitmap_vector_free (st_avout);

  nearer = sbitmap_vector_alloc (num_edges, n_exprs);

  /* Allocate an extra element for the entry block.  */
  nearerout = sbitmap_vector_alloc (last_basic_block + 1, n_exprs);
  compute_nearerout (edge_list, farthest, st_avloc, nearer, nearerout);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      dump_sbitmap_vector (dump_file, "nearerout", "", nearerout,
			   last_basic_block + 1);
      dump_sbitmap_vector (dump_file, "nearer", "", nearer, num_edges);
    }
#endif

  sbitmap_vector_free (farthest);

  *insert = sbitmap_vector_alloc (num_edges, n_exprs);
  *delete = sbitmap_vector_alloc (last_basic_block, n_exprs);
  compute_rev_insert_delete (edge_list, st_avloc, nearer, nearerout,
			     *insert, *delete);

  sbitmap_vector_free (nearerout);
  sbitmap_vector_free (nearer);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      dump_sbitmap_vector (dump_file, "pre_insert_map", "", *insert, num_edges);
      dump_sbitmap_vector (dump_file, "pre_delete_map", "", *delete,
			   last_basic_block);
    }
#endif
  return edge_list;
}