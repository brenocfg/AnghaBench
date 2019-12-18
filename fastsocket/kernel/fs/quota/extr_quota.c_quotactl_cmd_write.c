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
#define  Q_GETFMT 133 
#define  Q_GETINFO 132 
#define  Q_SYNC 131 
#define  Q_XGETQSTAT 130 
#define  Q_XGETQUOTA 129 
#define  Q_XQUOTASYNC 128 

__attribute__((used)) static int quotactl_cmd_write(int cmd)
{
	switch (cmd) {
	case Q_GETFMT:
	case Q_GETINFO:
	case Q_SYNC:
	case Q_XGETQSTAT:
	case Q_XGETQUOTA:
	case Q_XQUOTASYNC:
		return 0;
	}
	return 1;
}