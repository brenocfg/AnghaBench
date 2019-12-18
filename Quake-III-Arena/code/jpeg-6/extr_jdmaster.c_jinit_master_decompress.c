#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_decomp_master {int dummy; } ;
typedef  TYPE_3__* my_master_ptr ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_10__ {struct jpeg_decomp_master* master; TYPE_1__* mem; } ;
struct TYPE_8__ {int /*<<< orphan*/  is_dummy_pass; int /*<<< orphan*/  finish_output_pass; int /*<<< orphan*/  prepare_for_output_pass; } ;
struct TYPE_9__ {TYPE_2__ pub; } ;
struct TYPE_7__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_output_pass ; 
 int /*<<< orphan*/  master_selection (TYPE_4__*) ; 
 int /*<<< orphan*/  my_decomp_master ; 
 int /*<<< orphan*/  prepare_for_output_pass ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_master_decompress (j_decompress_ptr cinfo)
{
  my_master_ptr master;

  master = (my_master_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(my_decomp_master));
  cinfo->master = (struct jpeg_decomp_master *) master;
  master->pub.prepare_for_output_pass = prepare_for_output_pass;
  master->pub.finish_output_pass = finish_output_pass;

  master->pub.is_dummy_pass = FALSE;

  master_selection(cinfo);
}