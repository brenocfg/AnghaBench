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
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
#define  SN_HWPERF_OP_BUSY 134 
#define  SN_HWPERF_OP_INVAL 133 
#define  SN_HWPERF_OP_IO_ERROR 132 
#define  SN_HWPERF_OP_NOMEM 131 
#define  SN_HWPERF_OP_NO_PERM 130 
#define  SN_HWPERF_OP_OK 129 
#define  SN_HWPERF_OP_RECONFIGURE 128 

__attribute__((used)) static int sn_hwperf_map_err(int hwperf_err)
{
	int e;

	switch(hwperf_err) {
	case SN_HWPERF_OP_OK:
		e = 0;
		break;

	case SN_HWPERF_OP_NOMEM:
		e = -ENOMEM;
		break;

	case SN_HWPERF_OP_NO_PERM:
		e = -EPERM;
		break;

	case SN_HWPERF_OP_IO_ERROR:
		e = -EIO;
		break;

	case SN_HWPERF_OP_BUSY:
		e = -EBUSY;
		break;

	case SN_HWPERF_OP_RECONFIGURE:
		e = -EAGAIN;
		break;

	case SN_HWPERF_OP_INVAL:
	default:
		e = -EINVAL;
		break;
	}

	return e;
}