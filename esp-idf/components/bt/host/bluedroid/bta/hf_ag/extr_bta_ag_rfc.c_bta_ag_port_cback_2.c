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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  bta_ag_port_cback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void bta_ag_port_cback_2(UINT32 code, UINT16 handle) {bta_ag_port_cback(code, handle, 2);}