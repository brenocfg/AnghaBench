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
 int AP_DOMAINS ; 
 int /*<<< orphan*/  AP_MKQID (int,int) ; 
 int /*<<< orphan*/  ap_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_reset_all(void)
{
	int i, j;

	for (i = 0; i < AP_DOMAINS; i++)
		for (j = 0; j < AP_DEVICES; j++)
			ap_reset_queue(AP_MKQID(j, i));
}