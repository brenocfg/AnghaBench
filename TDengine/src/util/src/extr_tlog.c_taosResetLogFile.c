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
 int LOG_FILE_NAME_LEN ; 
 int /*<<< orphan*/  pPrint (char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int taosLogFlag ; 
 scalar_t__ taosLogLines ; 
 scalar_t__ taosLogMaxLines ; 
 char* taosLogName ; 
 int /*<<< orphan*/  taosOpenNewLogFile () ; 

void taosResetLogFile() {
  char lastName[LOG_FILE_NAME_LEN];
  sprintf(lastName, "%s.%d", taosLogName, taosLogFlag);

  // force create a new log file
  taosLogLines = taosLogMaxLines + 10;

  taosOpenNewLogFile();
  remove(lastName);

  pPrint("==================================");
  pPrint("   reset log file ");
}