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
struct rfcomm_dlc {int dummy; } ;

/* Variables and functions */
 int __rfcomm_dlc_close (struct rfcomm_dlc*,int) ; 
 int /*<<< orphan*/  rfcomm_lock () ; 
 int /*<<< orphan*/  rfcomm_unlock () ; 

int rfcomm_dlc_close(struct rfcomm_dlc *d, int err)
{
	int r;

	rfcomm_lock();

	r = __rfcomm_dlc_close(d, err);

	rfcomm_unlock();
	return r;
}