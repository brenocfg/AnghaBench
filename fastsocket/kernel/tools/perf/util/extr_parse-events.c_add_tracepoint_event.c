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
struct list_head {int dummy; } ;

/* Variables and functions */
 int add_tracepoint (struct list_head**,int*,char*,char*) ; 
 int add_tracepoint_multi_event (struct list_head**,int*,char*,char*) ; 
 scalar_t__ strpbrk (char*,char*) ; 

__attribute__((used)) static int add_tracepoint_event(struct list_head **list, int *idx,
				char *sys_name, char *evt_name)
{
	return strpbrk(evt_name, "*?") ?
	       add_tracepoint_multi_event(list, idx, sys_name, evt_name) :
	       add_tracepoint(list, idx, sys_name, evt_name);
}