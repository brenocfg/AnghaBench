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
typedef  TYPE_1__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_6__ {scalar_t__ global_state; } ;

/* Variables and functions */
 scalar_t__ DSTATE_INHEADER ; 
 scalar_t__ DSTATE_START ; 
 int /*<<< orphan*/  ERREXIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_NO_IMAGE ; 
 int JPEG_HEADER_OK ; 
 int JPEG_HEADER_TABLES_ONLY ; 
#define  JPEG_REACHED_EOI 130 
#define  JPEG_REACHED_SOS 129 
#define  JPEG_SUSPENDED 128 
 int /*<<< orphan*/  jpeg_abort (int /*<<< orphan*/ ) ; 
 int jpeg_consume_input (TYPE_1__*) ; 

int
jpeg_read_header (j_decompress_ptr cinfo, boolean require_image)
{
  int retcode;

  if (cinfo->global_state != DSTATE_START &&
      cinfo->global_state != DSTATE_INHEADER)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  retcode = jpeg_consume_input(cinfo);

  switch (retcode) {
  case JPEG_REACHED_SOS:
    retcode = JPEG_HEADER_OK;
    break;
  case JPEG_REACHED_EOI:
    if (require_image)		/* Complain if application wanted an image */
      ERREXIT(cinfo, JERR_NO_IMAGE);
    /* Reset to start state; it would be safer to require the application to
     * call jpeg_abort, but we can't change it now for compatibility reasons.
     * A side effect is to free any temporary memory (there shouldn't be any).
     */
    jpeg_abort((j_common_ptr) cinfo); /* sets state = DSTATE_START */
    retcode = JPEG_HEADER_TABLES_ONLY;
    break;
  case JPEG_SUSPENDED:
    /* no work */
    break;
  }

  return retcode;
}