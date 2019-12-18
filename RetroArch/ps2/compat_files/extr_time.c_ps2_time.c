#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ sceCdCLOCK ;

/* Variables and functions */
 scalar_t__ DEC (int /*<<< orphan*/ ) ; 
 scalar_t__ STARTING_YEAR ; 
 int /*<<< orphan*/  _gmtotime_t (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  configConvertToLocalTime (TYPE_1__*) ; 
 int /*<<< orphan*/  sceCdReadClock (TYPE_1__*) ; 

time_t ps2_time(time_t *t) {
   time_t tim;
   sceCdCLOCK clocktime; /* defined in libcdvd.h */

   sceCdReadClock(&clocktime); /* libcdvd.a */
   configConvertToLocalTime(&clocktime);

   tim =   _gmtotime_t (DEC(clocktime.year)+ STARTING_YEAR,
                        DEC(clocktime.month),
                        DEC(clocktime.day),
                        DEC(clocktime.hour),
                        DEC(clocktime.minute),
                        DEC(clocktime.second));

	if(t)
		*t = tim;

	return tim;
}