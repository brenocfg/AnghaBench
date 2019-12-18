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
struct auto_pin_cfg {size_t num_inputs; TYPE_1__* inputs; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int type; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 size_t AUTO_CFG_MAX_INS ; 

__attribute__((used)) static void add_auto_cfg_input_pin(struct auto_pin_cfg *cfg, hda_nid_t nid,
				   int type)
{
	if (cfg->num_inputs < AUTO_CFG_MAX_INS) {
		cfg->inputs[cfg->num_inputs].pin = nid;
		cfg->inputs[cfg->num_inputs].type = type;
		cfg->num_inputs++;
	}
}