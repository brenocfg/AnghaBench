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
struct TYPE_14__ {scalar_t__ global_state; TYPE_3__* dest; TYPE_1__* marker; TYPE_2__* err; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* term_destination ) (TYPE_4__*) ;int /*<<< orphan*/  (* init_destination ) (TYPE_4__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* reset_error_mgr ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* write_tables_only ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ CSTATE_START ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  jinit_marker_writer (TYPE_4__*) ; 
 int /*<<< orphan*/  jpeg_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

void
jpeg_write_tables (j_compress_ptr cinfo)
{
  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  /* (Re)initialize error mgr and destination modules */
  (*cinfo->err->reset_error_mgr) ((j_common_ptr) cinfo);
  (*cinfo->dest->init_destination) (cinfo);
  /* Initialize the marker writer ... bit of a crock to do it here. */
  jinit_marker_writer(cinfo);
  /* Write them tables! */
  (*cinfo->marker->write_tables_only) (cinfo);
  /* And clean up. */
  (*cinfo->dest->term_destination) (cinfo);
  /* We can use jpeg_abort to release memory. */
  jpeg_abort((j_common_ptr) cinfo);
}