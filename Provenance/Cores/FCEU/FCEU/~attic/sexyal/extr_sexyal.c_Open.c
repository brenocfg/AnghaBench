#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  SetConvert; int /*<<< orphan*/  CanWrite; int /*<<< orphan*/  Close; int /*<<< orphan*/  Write; } ;
typedef  int /*<<< orphan*/  SexyAL_format ;
typedef  TYPE_1__ SexyAL_device ;
typedef  int /*<<< orphan*/  SexyAL_buffering ;
typedef  int /*<<< orphan*/  SexyAL ;

/* Variables and functions */
 int /*<<< orphan*/  CanWrite ; 
 int /*<<< orphan*/  Close ; 
 int /*<<< orphan*/  SetConvert ; 
 TYPE_1__* SexyALI_DSound_Open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* SexyALI_OSS_Open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Write ; 

__attribute__((used)) static SexyAL_device *Open(SexyAL *iface, uint64_t id, SexyAL_format *format, SexyAL_buffering *buffering)
{
 SexyAL_device *ret;

 #ifdef WIN32
 if(!(ret=SexyALI_DSound_Open(id,format,buffering))) return(0);
 #else
 if(!(ret=SexyALI_OSS_Open(id,format,buffering))) return(0);
 #endif
 
 ret->Write=Write;
 ret->Close=Close;
 ret->CanWrite=CanWrite;
 ret->SetConvert=SetConvert;
 return(ret);
}