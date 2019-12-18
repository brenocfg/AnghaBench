#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* internal; TYPE_1__* oformat; } ;
struct TYPE_7__ {scalar_t__ streams_initialized; scalar_t__ initialized; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* deinit ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void deinit_muxer(AVFormatContext *s)
{
    if (s->oformat && s->oformat->deinit && s->internal->initialized)
        s->oformat->deinit(s);
    s->internal->initialized =
    s->internal->streams_initialized = 0;
}