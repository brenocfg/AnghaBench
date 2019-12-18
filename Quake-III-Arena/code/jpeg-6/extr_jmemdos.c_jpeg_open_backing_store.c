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
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  backing_store_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  JERR_TFILE_CREATE ; 
 scalar_t__ open_ems_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ open_file_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ open_xms_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

void
jpeg_open_backing_store (j_common_ptr cinfo, backing_store_ptr info,
			 long total_bytes_needed)
{
  /* Try extended memory, then expanded memory, then regular file. */
#if XMS_SUPPORTED
  if (open_xms_store(cinfo, info, total_bytes_needed))
    return;
#endif
#if EMS_SUPPORTED
  if (open_ems_store(cinfo, info, total_bytes_needed))
    return;
#endif
  if (open_file_store(cinfo, info, total_bytes_needed))
    return;
  ERREXITS(cinfo, JERR_TFILE_CREATE, "");
}