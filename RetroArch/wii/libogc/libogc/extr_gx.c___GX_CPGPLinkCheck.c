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
struct __gxfifo {scalar_t__ buf_start; scalar_t__ buf_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cpufifo ; 
 int /*<<< orphan*/  _gpfifo ; 
 int /*<<< orphan*/  _gxcpufifoready ; 
 int /*<<< orphan*/  _gxgpfifoready ; 

__attribute__((used)) static u32 __GX_CPGPLinkCheck()
{
	struct __gxfifo *gpfifo = (struct __gxfifo*)&_gpfifo;
	struct __gxfifo *cpufifo = (struct __gxfifo*)&_cpufifo;

	if(!_gxcpufifoready || !_gxgpfifoready) return 0;

	if((cpufifo->buf_start==gpfifo->buf_start)&&(cpufifo->buf_end==gpfifo->buf_end)) return 1;

	return 0;
}