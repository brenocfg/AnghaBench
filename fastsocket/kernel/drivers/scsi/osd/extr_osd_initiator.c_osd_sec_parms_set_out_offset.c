#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* data_out_integrity_check_offset; } ;
struct TYPE_3__ {void* data_out_integrity_check_offset; } ;
struct osd_security_parameters {TYPE_2__ v2; TYPE_1__ v1; } ;
typedef  void* osd_cdb_offset ;

/* Variables and functions */

__attribute__((used)) static inline void osd_sec_parms_set_out_offset(bool is_v1,
	struct osd_security_parameters *sec_parms, osd_cdb_offset offset)
{
	if (is_v1)
		sec_parms->v1.data_out_integrity_check_offset = offset;
	else
		sec_parms->v2.data_out_integrity_check_offset = offset;
}