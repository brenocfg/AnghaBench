#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* j_compress_ptr ;
struct TYPE_7__ {scalar_t__ next_scanline; scalar_t__ global_state; TYPE_1__* marker; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_any_marker ) (TYPE_2__*,int,int /*<<< orphan*/  const*,unsigned int) ;} ;
typedef  int /*<<< orphan*/  JOCTET ;

/* Variables and functions */
 scalar_t__ CSTATE_RAW_OK ; 
 scalar_t__ CSTATE_SCANNING ; 
 scalar_t__ CSTATE_WRCOEFS ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/  const*,unsigned int) ; 

void
jpeg_write_marker (j_compress_ptr cinfo, int marker,
		   const JOCTET *dataptr, unsigned int datalen)
{
  if (cinfo->next_scanline != 0 ||
      (cinfo->global_state != CSTATE_SCANNING &&
       cinfo->global_state != CSTATE_RAW_OK &&
       cinfo->global_state != CSTATE_WRCOEFS))
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  (*cinfo->marker->write_any_marker) (cinfo, marker, dataptr, datalen);
}