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
struct TYPE_5__ {int (* write ) (TYPE_2__*,char*,size_t,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__* RTMP_OS_FD ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char*,size_t,int /*<<< orphan*/ *) ; 

int RtmpOSFileWrite(RTMP_OS_FD osfd, char *pDataPtr, int writeLen)
{
	return osfd->f_op->write(osfd, pDataPtr, (size_t)writeLen, &osfd->f_pos);
}