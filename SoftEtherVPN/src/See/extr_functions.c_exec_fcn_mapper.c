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
typedef  int uint32 ;
typedef  int /*<<< orphan*/ * exec_fcn ;

/* Variables and functions */
#define  COUNT_PACKETS 129 
#define  TCP_SESSION 128 
 int /*<<< orphan*/  count_packets ; 
 int /*<<< orphan*/  tcp_session ; 

exec_fcn exec_fcn_mapper(uint32 index)
{
	switch (index)
	{
	case COUNT_PACKETS:
		return (exec_fcn) count_packets;
	
	case TCP_SESSION:
		return (exec_fcn) tcp_session;
	default:
		return NULL;
	}
	
	return NULL;
}