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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int) ; 

__attribute__((used)) static void print_eisa_id(char *s, u_int32_t id)
{
	char vendor[4];
	int rev;
	int device;
	
	rev = id & 0xff;
	id >>= 8;
	device = id & 0xff;
	id >>= 8;
	vendor[3] = '\0';
	vendor[2] = '@' + (id & 0x1f);
	id >>= 5;	
	vendor[1] = '@' + (id & 0x1f);
	id >>= 5;	
	vendor[0] = '@' + (id & 0x1f);
	id >>= 5;	
	
	sprintf(s, "%s%02X%02X", vendor, device, rev);
}