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
struct TYPE_5__ {int /*<<< orphan*/  (* frame_cb ) (void const*,unsigned int,unsigned int,size_t) ;} ;
struct TYPE_6__ {TYPE_1__ cbs; } ;
typedef  TYPE_2__ netplay_t ;

/* Variables and functions */
 TYPE_2__* netplay_data ; 
 int /*<<< orphan*/  netplay_should_skip (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (void const*,unsigned int,unsigned int,size_t) ; 

void video_frame_net(const void *data, unsigned width,
      unsigned height, size_t pitch)
{
   netplay_t *netplay = netplay_data;
   if (!netplay_should_skip(netplay))
      netplay->cbs.frame_cb(data, width, height, pitch);
}