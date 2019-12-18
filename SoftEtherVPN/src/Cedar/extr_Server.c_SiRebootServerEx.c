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
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiRebootServerThread ; 
 int server_reset_setting ; 

void SiRebootServerEx(bool bridge, bool reset_setting)
{
	THREAD *t;

	server_reset_setting = reset_setting;

	t = NewThread(SiRebootServerThread, (void *)bridge);
	ReleaseThread(t);
}