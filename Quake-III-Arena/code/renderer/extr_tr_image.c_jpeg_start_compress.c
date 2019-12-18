#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_14__ {scalar_t__ global_state; scalar_t__ raw_data_in; scalar_t__ next_scanline; TYPE_2__* master; TYPE_1__* dest; TYPE_3__* err; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* reset_error_mgr ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* prepare_for_pass ) (TYPE_4__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* init_destination ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ CSTATE_RAW_OK ; 
 scalar_t__ CSTATE_SCANNING ; 
 scalar_t__ CSTATE_START ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  jinit_compress_master (TYPE_4__*) ; 
 int /*<<< orphan*/  jpeg_suppress_tables (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

void
jpeg_start_compress (j_compress_ptr cinfo, boolean write_all_tables)
{
  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  if (write_all_tables)
    jpeg_suppress_tables(cinfo, FALSE);	/* mark all tables to be written */

  /* (Re)initialize error mgr and destination modules */
  (*cinfo->err->reset_error_mgr) ((j_common_ptr) cinfo);
  (*cinfo->dest->init_destination) (cinfo);
  /* Perform master selection of active modules */
  jinit_compress_master(cinfo);
  /* Set up for the first pass */
  (*cinfo->master->prepare_for_pass) (cinfo);
  /* Ready for application to drive first pass through jpeg_write_scanlines
   * or jpeg_write_raw_data.
   */
  cinfo->next_scanline = 0;
  cinfo->global_state = (cinfo->raw_data_in ? CSTATE_RAW_OK : CSTATE_SCANNING);
}