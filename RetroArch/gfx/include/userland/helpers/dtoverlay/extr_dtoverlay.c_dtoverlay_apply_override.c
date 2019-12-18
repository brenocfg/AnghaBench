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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int dtoverlay_foreach_override_target (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dtoverlay_override_one_target ; 

int dtoverlay_apply_override(DTBLOB_T *dtb, const char *override_name,
                             const char *override_data, int data_len,
                             const char *override_value)
{
   return dtoverlay_foreach_override_target(dtb, override_name,
					    override_data, data_len,
					    dtoverlay_override_one_target,
					    (void *)override_value);
}