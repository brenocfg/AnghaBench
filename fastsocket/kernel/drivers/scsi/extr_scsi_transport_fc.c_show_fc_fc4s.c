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
typedef  int u8 ;

/* Variables and functions */
 int FC_FC4_LIST_SIZE ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int
show_fc_fc4s (char *buf, u8 *fc4_list)
{
	int i, len=0;

	for (i = 0; i < FC_FC4_LIST_SIZE; i++, fc4_list++)
		len += sprintf(buf + len , "0x%02x ", *fc4_list);
	len += sprintf(buf + len, "\n");
	return len;
}