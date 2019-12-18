#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  f_pos; TYPE_1__* f_op; } ;
struct TYPE_5__ {int (* read ) (TYPE_2__*,char*,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__* RTMP_OS_FD ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 int stub1 (TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 

int RtmpOSFileRead(RTMP_OS_FD osfd, char *pDataPtr, int readLen)
{
	// The object must have a read method
	if (osfd->f_op && osfd->f_op->read)
	{
		return osfd->f_op->read(osfd,  pDataPtr, readLen, &osfd->f_pos);
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("no file read method\n"));
		return -1;
	}
}