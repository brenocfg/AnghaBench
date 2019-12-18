#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int code; } ;
struct chsc_async_area {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHSC_LOG_HEX (int /*<<< orphan*/ ,struct chsc_async_area*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void chsc_log_command(struct chsc_async_area *chsc_area)
{
	char dbf[10];

	sprintf(dbf, "CHSC:%x", chsc_area->header.code);
	CHSC_LOG(0, dbf);
	CHSC_LOG_HEX(0, chsc_area, 32);
}