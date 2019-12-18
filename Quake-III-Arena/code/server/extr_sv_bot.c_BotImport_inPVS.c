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
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int SV_inPVS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int BotImport_inPVS(vec3_t p1, vec3_t p2) {
	return SV_inPVS (p1, p2);
}