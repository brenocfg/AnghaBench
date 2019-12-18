#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jvirt_barray_ptr ;
typedef  TYPE_3__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_11__ {scalar_t__ global_state; scalar_t__ next_scanline; TYPE_2__* dest; TYPE_1__* err; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* init_destination ) (TYPE_3__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* reset_error_mgr ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CSTATE_START ; 
 scalar_t__ CSTATE_WRCOEFS ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  jpeg_suppress_tables (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  transencode_master_selection (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
jpeg_write_coefficients (j_compress_ptr cinfo, jvirt_barray_ptr * coef_arrays)
{
  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Mark all tables to be written */
  jpeg_suppress_tables(cinfo, FALSE);
  /* (Re)initialize error mgr and destination modules */
  (*cinfo->err->reset_error_mgr) ((j_common_ptr) cinfo);
  (*cinfo->dest->init_destination) (cinfo);
  /* Perform master selection of active modules */
  transencode_master_selection(cinfo, coef_arrays);
  /* Wait for jpeg_finish_compress() call */
  cinfo->next_scanline = 0;	/* so jpeg_write_marker works */
  cinfo->global_state = CSTATE_WRCOEFS;
}