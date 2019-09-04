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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HUB ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_RETRY_INTERVAL ; 
 int /*<<< orphan*/  SetRadiusServerEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void SetRadiusServer(HUB *hub, char *name, UINT port, char *secret)
{
	SetRadiusServerEx(hub, name, port, secret, RADIUS_RETRY_INTERVAL);
}