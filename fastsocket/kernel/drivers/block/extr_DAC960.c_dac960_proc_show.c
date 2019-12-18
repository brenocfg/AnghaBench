#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {scalar_t__ MonitoringAlertMode; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int DAC960_ControllerCount ; 
 TYPE_1__** DAC960_Controllers ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,unsigned char*) ; 

__attribute__((used)) static int dac960_proc_show(struct seq_file *m, void *v)
{
  unsigned char *StatusMessage = "OK\n";
  int ControllerNumber;
  for (ControllerNumber = 0;
       ControllerNumber < DAC960_ControllerCount;
       ControllerNumber++)
    {
      DAC960_Controller_T *Controller = DAC960_Controllers[ControllerNumber];
      if (Controller == NULL) continue;
      if (Controller->MonitoringAlertMode)
	{
	  StatusMessage = "ALERT\n";
	  break;
	}
    }
  seq_puts(m, StatusMessage);
  return 0;
}