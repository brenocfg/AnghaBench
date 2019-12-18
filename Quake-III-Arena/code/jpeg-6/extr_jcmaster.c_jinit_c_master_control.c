#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct jpeg_comp_master {int dummy; } ;
typedef  TYPE_3__* my_master_ptr ;
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_12__ {int num_scans; scalar_t__ optimize_coding; void* progressive_mode; int /*<<< orphan*/ * scan_info; struct jpeg_comp_master* master; TYPE_1__* mem; } ;
struct TYPE_10__ {void* is_last_pass; int /*<<< orphan*/  finish_pass; int /*<<< orphan*/  pass_startup; int /*<<< orphan*/  prepare_for_pass; } ;
struct TYPE_11__ {int total_passes; scalar_t__ pass_number; scalar_t__ scan_number; int /*<<< orphan*/  pass_type; TYPE_2__ pub; } ;
struct TYPE_9__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  JERR_NOT_COMPILED ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  finish_pass_master ; 
 int /*<<< orphan*/  huff_opt_pass ; 
 int /*<<< orphan*/  initial_setup (TYPE_4__*) ; 
 int /*<<< orphan*/  main_pass ; 
 int /*<<< orphan*/  my_comp_master ; 
 int /*<<< orphan*/  output_pass ; 
 int /*<<< orphan*/  pass_startup ; 
 int /*<<< orphan*/  prepare_for_pass ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_script (TYPE_4__*) ; 

void
jinit_c_master_control (j_compress_ptr cinfo, boolean transcode_only)
{
  my_master_ptr master;

  master = (my_master_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(my_comp_master));
  cinfo->master = (struct jpeg_comp_master *) master;
  master->pub.prepare_for_pass = prepare_for_pass;
  master->pub.pass_startup = pass_startup;
  master->pub.finish_pass = finish_pass_master;
  master->pub.is_last_pass = FALSE;

  /* Validate parameters, determine derived values */
  initial_setup(cinfo);

  if (cinfo->scan_info != NULL) {
#ifdef C_MULTISCAN_FILES_SUPPORTED
    validate_script(cinfo);
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else {
    cinfo->progressive_mode = FALSE;
    cinfo->num_scans = 1;
  }

  if (cinfo->progressive_mode)	/*  TEMPORARY HACK ??? */
    cinfo->optimize_coding = TRUE; /* assume default tables no good for progressive mode */

  /* Initialize my private state */
  if (transcode_only) {
    /* no main pass in transcoding */
    if (cinfo->optimize_coding)
      master->pass_type = huff_opt_pass;
    else
      master->pass_type = output_pass;
  } else {
    /* for normal compression, first pass is always this type: */
    master->pass_type = main_pass;
  }
  master->scan_number = 0;
  master->pass_number = 0;
  if (cinfo->optimize_coding)
    master->total_passes = cinfo->num_scans * 2;
  else
    master->total_passes = cinfo->num_scans;
}