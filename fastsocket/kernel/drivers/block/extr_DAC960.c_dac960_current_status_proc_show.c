#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct TYPE_6__ {scalar_t__ LastCurrentStatusTime; size_t CurrentStatusLength; int ProgressBufferLength; unsigned char* CurrentStatusBuffer; unsigned char* ProgressBuffer; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_AnnounceDriver (TYPE_1__*) ; 
 scalar_t__ DAC960_CheckStatusBuffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  DAC960_ReportControllerConfiguration (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_ReportDeviceConfiguration (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  strcpy (unsigned char*,unsigned char*) ; 
 int strlen (unsigned char*) ; 

__attribute__((used)) static int dac960_current_status_proc_show(struct seq_file *m, void *v)
{
  DAC960_Controller_T *Controller = (DAC960_Controller_T *) m->private;
  unsigned char *StatusMessage =
    "No Rebuild or Consistency Check in Progress\n";
  int ProgressMessageLength = strlen(StatusMessage);
  if (jiffies != Controller->LastCurrentStatusTime)
    {
      Controller->CurrentStatusLength = 0;
      DAC960_AnnounceDriver(Controller);
      DAC960_ReportControllerConfiguration(Controller);
      DAC960_ReportDeviceConfiguration(Controller);
      if (Controller->ProgressBufferLength > 0)
	ProgressMessageLength = Controller->ProgressBufferLength;
      if (DAC960_CheckStatusBuffer(Controller, 2 + ProgressMessageLength))
	{
	  unsigned char *CurrentStatusBuffer = Controller->CurrentStatusBuffer;
	  CurrentStatusBuffer[Controller->CurrentStatusLength++] = ' ';
	  CurrentStatusBuffer[Controller->CurrentStatusLength++] = ' ';
	  if (Controller->ProgressBufferLength > 0)
	    strcpy(&CurrentStatusBuffer[Controller->CurrentStatusLength],
		   Controller->ProgressBuffer);
	  else
	    strcpy(&CurrentStatusBuffer[Controller->CurrentStatusLength],
		   StatusMessage);
	  Controller->CurrentStatusLength += ProgressMessageLength;
	}
      Controller->LastCurrentStatusTime = jiffies;
    }
	seq_printf(m, "%.*s", Controller->CurrentStatusLength, Controller->CurrentStatusBuffer);
	return 0;
}