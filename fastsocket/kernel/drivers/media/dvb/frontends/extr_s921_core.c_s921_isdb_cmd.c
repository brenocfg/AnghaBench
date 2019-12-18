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
typedef  int u32 ;
struct s921_isdb_t {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ISDB_T_CMD_GET_STATUS 131 
#define  ISDB_T_CMD_INIT 130 
#define  ISDB_T_CMD_SET_PARAM 129 
#define  ISDB_T_CMD_TUNE 128 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  s921_isdb_get_status (struct s921_isdb_t*,void*) ; 
 int /*<<< orphan*/  s921_isdb_init (struct s921_isdb_t*) ; 
 int /*<<< orphan*/  s921_isdb_set_parameters (struct s921_isdb_t*,void*) ; 
 int /*<<< orphan*/  s921_isdb_tune (struct s921_isdb_t*,void*) ; 

int s921_isdb_cmd(struct s921_isdb_t *dev, u32 cmd, void *data) {
	switch(cmd) {
	case ISDB_T_CMD_INIT:
		s921_isdb_init(dev);
		break;
	case ISDB_T_CMD_SET_PARAM:
		s921_isdb_set_parameters(dev, data);
		break;
	case ISDB_T_CMD_TUNE:
		s921_isdb_tune(dev, data);
		break;
	case ISDB_T_CMD_GET_STATUS:
		s921_isdb_get_status(dev, data);
		break;
	default:
		printk("unhandled command\n");
		return -EINVAL;
	}
	return 0;
}