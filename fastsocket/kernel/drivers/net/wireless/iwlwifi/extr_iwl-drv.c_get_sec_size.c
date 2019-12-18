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
struct iwl_firmware_pieces {TYPE_2__* img; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;
struct TYPE_4__ {TYPE_1__* sec; } ;
struct TYPE_3__ {size_t size; } ;

/* Variables and functions */

__attribute__((used)) static size_t get_sec_size(struct iwl_firmware_pieces *pieces,
			   enum iwl_ucode_type type,
			   int sec)
{
	return pieces->img[type].sec[sec].size;
}