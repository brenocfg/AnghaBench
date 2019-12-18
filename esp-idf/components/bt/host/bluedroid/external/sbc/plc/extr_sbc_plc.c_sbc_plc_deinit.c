#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hist; scalar_t__ bestlag; scalar_t__ nbf; } ;
typedef  TYPE_1__ sbc_plc_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void sbc_plc_deinit(sbc_plc_state_t *plc_state){
    plc_state->nbf=0;
    plc_state->bestlag=0;
    memset(plc_state->hist, 0, sizeof(plc_state->hist));
}