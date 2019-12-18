#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ second; scalar_t__ minute; scalar_t__ hour; scalar_t__ day; scalar_t__ month; scalar_t__ year; } ;
struct TYPE_6__ {scalar_t__ seconds; scalar_t__ minutes; scalar_t__ hours; } ;
struct TYPE_7__ {TYPE_1__ last_played; TYPE_2__ runtime; } ;
typedef  TYPE_3__ runtime_log_t ;

/* Variables and functions */

void runtime_log_reset(runtime_log_t *runtime_log)
{
   if (!runtime_log)
      return;
   
   runtime_log->runtime.hours      = 0;
   runtime_log->runtime.minutes    = 0;
   runtime_log->runtime.seconds    = 0;
   
   runtime_log->last_played.year   = 0;
   runtime_log->last_played.month  = 0;
   runtime_log->last_played.day    = 0;
   runtime_log->last_played.hour   = 0;
   runtime_log->last_played.minute = 0;
   runtime_log->last_played.second = 0;
}