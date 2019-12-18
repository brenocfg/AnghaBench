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
struct wlapi_timer {int dummy; } ;
struct brcms_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_free_timer (struct brcms_timer*) ; 

void wlapi_free_timer(struct wlapi_timer *t)
{
	brcms_free_timer((struct brcms_timer *)t);
}