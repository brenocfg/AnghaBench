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
struct TYPE_5__ {size_t (* sample_batch_cb ) (int /*<<< orphan*/  const*,size_t) ;} ;
struct TYPE_6__ {TYPE_1__ cbs; int /*<<< orphan*/  stall; } ;
typedef  TYPE_2__ netplay_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 TYPE_2__* netplay_data ; 
 int /*<<< orphan*/  netplay_should_skip (TYPE_2__*) ; 
 size_t stub1 (int /*<<< orphan*/  const*,size_t) ; 

size_t audio_sample_batch_net(const int16_t *data, size_t frames)
{
   netplay_t *netplay = netplay_data;
   if (!netplay_should_skip(netplay) && !netplay->stall)
      return netplay->cbs.sample_batch_cb(data, frames);
   return frames;
}