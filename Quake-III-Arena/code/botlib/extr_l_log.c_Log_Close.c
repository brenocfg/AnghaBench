#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  filename; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ botimport ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__ logfile ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void Log_Close(void)
{
	if (!logfile.fp) return;
	if (fclose(logfile.fp))
	{
		botimport.Print(PRT_ERROR, "can't close log file %s\n", logfile.filename);
		return;
	} //end if
	logfile.fp = NULL;
	botimport.Print(PRT_MESSAGE, "Closed log %s\n", logfile.filename);
}