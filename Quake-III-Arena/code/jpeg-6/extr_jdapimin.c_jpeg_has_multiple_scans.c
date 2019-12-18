#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_6__ {scalar_t__ global_state; TYPE_1__* inputctl; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_multiple_scans; } ;

/* Variables and functions */
 scalar_t__ DSTATE_READY ; 
 scalar_t__ DSTATE_STOPPING ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 

boolean
jpeg_has_multiple_scans (j_decompress_ptr cinfo)
{
  /* Only valid after jpeg_read_header completes */
  if (cinfo->global_state < DSTATE_READY ||
      cinfo->global_state > DSTATE_STOPPING)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  return cinfo->inputctl->has_multiple_scans;
}