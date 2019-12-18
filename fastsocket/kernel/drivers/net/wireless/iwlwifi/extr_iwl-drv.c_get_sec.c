#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_firmware_pieces {TYPE_1__* img; } ;
struct fw_sec {int dummy; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;
struct TYPE_2__ {struct fw_sec* sec; } ;

/* Variables and functions */

__attribute__((used)) static struct fw_sec *get_sec(struct iwl_firmware_pieces *pieces,
			      enum iwl_ucode_type type,
			      int  sec)
{
	return &pieces->img[type].sec[sec];
}