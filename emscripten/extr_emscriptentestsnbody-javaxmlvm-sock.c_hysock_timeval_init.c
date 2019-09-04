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
struct hytimeval_struct {int dummy; } ;
typedef  TYPE_2__* hytimeval_t ;
typedef  void* U_32 ;
struct TYPE_5__ {void* tv_usec; void* tv_sec; } ;
struct TYPE_6__ {TYPE_1__ time; } ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

I_32 hysock_timeval_init (U_32 secTime, U_32 uSecTime, hytimeval_t timeP)
{
    memset (timeP, 0, sizeof (struct hytimeval_struct));
    timeP->time.tv_sec = secTime;
    timeP->time.tv_usec = uSecTime;
    
    return 0;
}