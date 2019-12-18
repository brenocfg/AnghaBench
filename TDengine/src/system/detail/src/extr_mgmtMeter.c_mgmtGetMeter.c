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
typedef  int /*<<< orphan*/  STabObj ;

/* Variables and functions */
 int /*<<< orphan*/  meterSdb ; 
 scalar_t__ sdbGetRow (int /*<<< orphan*/ ,char*) ; 

STabObj *mgmtGetMeter(char *meterId) { return (STabObj *)sdbGetRow(meterSdb, meterId); }