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
 int /*<<< orphan*/  compute_earliest (struct edge_list*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_insert_delete (struct edge_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_laterin (struct edge_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct edge_list* create_edge_list () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_sbitmap_vector (scalar_t__,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int last_basic_block ; 
 int /*<<< orphan*/  print_edge_list (scalar_t__,struct edge_list*) ; 
 int /*<<< orphan*/ * sbitmap_vector_alloc (int,int) ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_edge_list (scalar_t__,struct edge_list*) ; 

struct edge_list *
pre_edge_lcm (int n_exprs, sbitmap *transp,
	      sbitmap *avloc, sbitmap *antloc, sbitmap *kill,
	      sbitmap **insert, sbitmap **delete)
{
  sbitmap *antin, *antout, *earliest;
  sbitmap *avin, *avout;
  sbitmap *later, *laterin;
  struct edge_list *edge_list;
  int num_edges;

  edge_list = create_edge_list ();
  num_edges = NUM_EDGES (edge_list);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      fprintf (dump_file, "Edge List:\n");
      verify_edge_list (dump_file, edge_list);
      print_edge_list (dump_file, edge_list);
      dump_sbitmap_vector (dump_file, "transp", "", transp, last_basic_block);
      dump_sbitmap_vector (dump_file, "antloc", "", antloc, last_basic_block);
      dump_sbitmap_vector (dump_file, "avloc", "", avloc, last_basic_block);
      dump_sbitmap_vector (dump_file, "kill", "", kill, last_basic_block);
    }
#endif

  /* Compute global availability.  */
  avin = sbitmap_vector_alloc (last_basic_block, n_exprs);
  avout = sbitmap_vector_alloc (last_basic_block, n_exprs);
  compute_available (avloc, kill, avout, avin);
  sbitmap_vector_free (avin);

  /* Compute global anticipatability.  */
  antin = sbitmap_vector_alloc (last_basic_block, n_exprs);
  antout = sbitmap_vector_alloc (last_basic_block, n_exprs);
  compute_antinout_edge (antloc, transp, antin, antout);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      dump_sbitmap_vector (dump_file, "antin", "", antin, last_basic_block);
      dump_sbitmap_vector (dump_file, "antout", "", antout, last_basic_block);
    }
#endif

  /* Compute earliestness.  */
  earliest = sbitmap_vector_alloc (num_edges, n_exprs);
  compute_earliest (edge_list, n_exprs, antin, antout, avout, kill, earliest);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    dump_sbitmap_vector (dump_file, "earliest", "", earliest, num_edges);
#endif

  sbitmap_vector_free (antout);
  sbitmap_vector_free (antin);
  sbitmap_vector_free (avout);

  later = sbitmap_vector_alloc (num_edges, n_exprs);

  /* Allocate an extra element for the exit block in the laterin vector.  */
  laterin = sbitmap_vector_alloc (last_basic_block + 1, n_exprs);
  compute_laterin (edge_list, earliest, antloc, later, laterin);

#ifdef LCM_DEBUG_INFO
  if (dump_file)
    {
      dump_sbitmap_vector (dump_file, "laterin", "", laterin, last_basic_block + 1);
      dump_sbitmap_vector (dump_file, "later", "", later, num_edges);
    }
#endif

  sbitmap_vector_free (earliest);

  *insert = sbitmap_vector_alloc (num_edges, n_exprs);
  *delete = sbitmap_vector_alloc (last_basic_block, n_exprs);
  compute_insert_delete (edge_list, antloc, later, laterin, *insert, *delete);

  sbitmap_vector_free (laterin);
  sbitmap_vector_free (later);

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