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
struct TYPE_2__ {char* filename; scalar_t__ fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LOGFILENAMESIZE ; 
 scalar_t__ fopen (char*,char*) ; 
 TYPE_1__ logfile ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

void Log_Open(char *filename)
{
	if (!filename || !strlen(filename))
	{
		printf("openlog <filename>\n");
		return;
	} //end if
	if (logfile.fp)
	{
		printf("log file %s is already opened\n", logfile.filename);
		return;
	} //end if
	logfile.fp = fopen(filename, "wb");
	if (!logfile.fp)
	{
		printf("can't open the log file %s\n", filename);
		return;
	} //end if
	strncpy(logfile.filename, filename, MAX_LOGFILENAMESIZE);
	printf("Opened log %s\n", logfile.filename);
}