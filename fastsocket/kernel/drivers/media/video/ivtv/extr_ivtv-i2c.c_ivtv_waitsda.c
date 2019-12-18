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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int ivtv_getsda (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_scldelay (struct ivtv*) ; 

__attribute__((used)) static int ivtv_waitsda(struct ivtv *itv, int val)
{
	int i;

	ivtv_scldelay(itv);
	for (i = 0; i < 1000; ++i) {
		if (ivtv_getsda(itv) == val)
			return 1;
	}
	return 0;
}