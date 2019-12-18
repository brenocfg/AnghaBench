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
struct __SexyAL_device {int /*<<< orphan*/  srcformat; } ;
typedef  int /*<<< orphan*/  SexyAL_format ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int SetConvert(struct __SexyAL_device *device, SexyAL_format *format)
{
 memcpy(&device->srcformat,format,sizeof(SexyAL_format));
 return(1);
}