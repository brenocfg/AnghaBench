#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fenceValue; int /*<<< orphan*/  fenceEvent; int /*<<< orphan*/  fence; } ;
struct TYPE_5__ {TYPE_1__ queue; } ;
typedef  TYPE_2__ d3d12_video_t ;

/* Variables and functions */
 scalar_t__ D3D12GetCompletedValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D12SetEventOnCompletion (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d12_gfx_sync(d3d12_video_t* d3d12)
{
   if (D3D12GetCompletedValue(d3d12->queue.fence) < d3d12->queue.fenceValue)
   {
      D3D12SetEventOnCompletion(
            d3d12->queue.fence, d3d12->queue.fenceValue, d3d12->queue.fenceEvent);
      WaitForSingleObject(d3d12->queue.fenceEvent, INFINITE);
   }
}