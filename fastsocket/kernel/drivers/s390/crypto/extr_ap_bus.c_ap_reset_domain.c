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

/* Variables and functions */
 int AP_DEVICES ; 
 int /*<<< orphan*/  AP_MKQID (int,int) ; 
 int ap_domain_index ; 
 int /*<<< orphan*/  ap_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_reset_domain(void)
{
	int i;

	if (ap_domain_index != -1)
		for (i = 0; i < AP_DEVICES; i++)
			ap_reset_queue(AP_MKQID(i, ap_domain_index));
}