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
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int transport_cmd_check_stop (struct se_cmd*,int) ; 

__attribute__((used)) static int transport_cmd_check_stop_to_fabric(struct se_cmd *cmd)
{
	return transport_cmd_check_stop(cmd, true);
}