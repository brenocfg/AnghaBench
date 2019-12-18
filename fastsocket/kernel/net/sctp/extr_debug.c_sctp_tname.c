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
struct TYPE_3__ {size_t timeout; } ;
typedef  TYPE_1__ sctp_subtype_t ;

/* Variables and functions */
 size_t SCTP_EVENT_TIMEOUT_MAX ; 
 char const** sctp_timer_tbl ; 

const char *sctp_tname(const sctp_subtype_t id)
{
	if (id.timeout <= SCTP_EVENT_TIMEOUT_MAX)
		return sctp_timer_tbl[id.timeout];
	return "unknown_timer";
}