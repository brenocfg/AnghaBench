#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jpeg_entropy_encoder {int dummy; } ;
typedef  TYPE_3__* phuff_entropy_ptr ;
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_9__ {struct jpeg_entropy_encoder* entropy; TYPE_2__* mem; } ;
struct TYPE_6__ {int /*<<< orphan*/  start_pass; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bit_buffer; int /*<<< orphan*/ ** count_ptrs; int /*<<< orphan*/ ** derived_tbls; TYPE_1__ pub; } ;
struct TYPE_7__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int NUM_HUFF_TBLS ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phuff_entropy_encoder ; 
 int /*<<< orphan*/  start_pass_phuff ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_phuff_encoder (j_compress_ptr cinfo)
{
  phuff_entropy_ptr entropy;
  int i;

  entropy = (phuff_entropy_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(phuff_entropy_encoder));
  cinfo->entropy = (struct jpeg_entropy_encoder *) entropy;
  entropy->pub.start_pass = start_pass_phuff;

  /* Mark tables unallocated */
  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    entropy->derived_tbls[i] = NULL;
    entropy->count_ptrs[i] = NULL;
  }
  entropy->bit_buffer = NULL;	/* needed only in AC refinement scan */
}