#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* stc; void* pts; int /*<<< orphan*/  started; } ;
typedef  void* TIME_T ;
typedef  TYPE_1__ CLOCK_STREAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_TRUE ; 

__attribute__((used)) static void clock_start_stream(CLOCK_STREAM_T *stream, TIME_T stc, TIME_T pts)
{
   stream->started = MMAL_TRUE;
   stream->pts = pts;
   stream->stc = stc;
}