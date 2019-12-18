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
struct ultrastor_config {int mscp_free; TYPE_1__* mscp; } ;
struct TYPE_2__ {char target_id; } ;

/* Variables and functions */
 int ULTRASTOR_MAX_CMDS ; 
 int /*<<< orphan*/  printk (char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static void log_ultrastor_abort(struct ultrastor_config *config,
				int command)
{
  static char fmt[80] = "abort %d (%x); MSCP free pool: %x;";
  int i;

  for (i = 0; i < ULTRASTOR_MAX_CMDS; i++)
    {
      fmt[20 + i*2] = ' ';
      if (! (config->mscp_free & (1 << i)))
	fmt[21 + i*2] = '0' + config->mscp[i].target_id;
      else
	fmt[21 + i*2] = '-';
    }
  fmt[20 + ULTRASTOR_MAX_CMDS * 2] = '\n';
  fmt[21 + ULTRASTOR_MAX_CMDS * 2] = 0;
  printk(fmt, command, &config->mscp[command], config->mscp_free);

}