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
struct mem_ref {int dummy; } ;
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gather_mem_refs_stmt (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_ref**) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memref_eq ; 
 int /*<<< orphan*/  memref_hash ; 

__attribute__((used)) static struct mem_ref *
gather_mem_refs (struct loop *loop, bitmap clobbered_vops)
{
  basic_block *body = get_loop_body (loop);
  block_stmt_iterator bsi;
  unsigned i;
  struct mem_ref *mem_ref_list = NULL;
  htab_t mem_refs = htab_create (100, memref_hash, memref_eq, NULL);

  for (i = 0; i < loop->num_nodes; i++)
    {
      for (bsi = bsi_start (body[i]); !bsi_end_p (bsi); bsi_next (&bsi))
	gather_mem_refs_stmt (loop, mem_refs, clobbered_vops, bsi_stmt (bsi),
			      &mem_ref_list);
    }

  free (body);

  htab_delete (mem_refs);
  return mem_ref_list;
}