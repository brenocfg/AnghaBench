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
struct hdsp {int period_bytes; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int hdsp_decode_latency (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdsp_compute_period_size(struct hdsp *hdsp)
{
	hdsp->period_bytes = 1 << ((hdsp_decode_latency(hdsp->control_register) + 8));
}