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
typedef  void* u16 ;

/* Variables and functions */
 void* __ntd_pid ; 
 void* __ntd_vid ; 
 int __ntd_vid_pid_specified ; 

void __ntd_set_pid_vid(u16 vid,u16 pid)
{
	__ntd_vid = vid;
	__ntd_pid = pid;
	__ntd_vid_pid_specified = 1;
}