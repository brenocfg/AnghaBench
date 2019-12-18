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

/* Variables and functions */
 int** link_addr ; 
 size_t linkcount ; 
 int slave ; 

add_to_linker(int addr,int target,int ext)
{
  link_addr[linkcount][0]=addr;
  link_addr[linkcount][1]=target|slave;
  link_addr[linkcount][2]=ext;  
  linkcount++;
}