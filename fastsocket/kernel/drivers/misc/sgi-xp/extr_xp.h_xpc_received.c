#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* received ) (short,int,void*) ;} ;

/* Variables and functions */
 void stub1 (short,int,void*) ; 
 TYPE_1__ xpc_interface ; 

__attribute__((used)) static inline void
xpc_received(short partid, int ch_number, void *payload)
{
	return xpc_interface.received(partid, ch_number, payload);
}