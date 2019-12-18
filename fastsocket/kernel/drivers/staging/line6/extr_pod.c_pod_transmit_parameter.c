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
struct usb_line6_pod {int /*<<< orphan*/  dumpreq; int /*<<< orphan*/  line6; } ;

/* Variables and functions */
 int POD_amp_model_setup ; 
 int POD_effect_setup ; 
 int /*<<< orphan*/  line6_invalidate_current (int /*<<< orphan*/ *) ; 
 scalar_t__ line6_transmit_parameter (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pod_store_parameter (struct usb_line6_pod*,int,int) ; 

void pod_transmit_parameter(struct usb_line6_pod *pod, int param, int value)
{
	if (line6_transmit_parameter(&pod->line6, param, value) == 0)
		pod_store_parameter(pod, param, value);

	if ((param == POD_amp_model_setup) || (param == POD_effect_setup))  /* these also affect other settings */
		line6_invalidate_current(&pod->dumpreq);
}