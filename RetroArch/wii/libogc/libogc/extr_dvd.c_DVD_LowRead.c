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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;
struct TYPE_2__ {int /*<<< orphan*/  offset; void* len; void* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __DoRead (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ __dvd_cmd_curr ; 
 void** _diReg ; 

s32 DVD_LowRead(void *buf,u32 len,s64 offset,dvdcallbacklow cb)
{
	_diReg[6] = len;

	__dvd_cmd_curr.buf = buf;
	__dvd_cmd_curr.len = len;
	__dvd_cmd_curr.offset = offset;
	__DoRead(buf,len,offset,cb);
	return 1;
}