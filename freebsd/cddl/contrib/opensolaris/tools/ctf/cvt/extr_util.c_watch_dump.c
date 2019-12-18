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
 int /*<<< orphan*/  printf (char*,...) ; 
 char* watch_address ; 
 int watch_length ; 

void
watch_dump(int v)
{
	char *p = watch_address;
	int i;

	if (watch_address == NULL || watch_length == 0)
		return;

	printf("%d: watch %p len %d\n",v,watch_address,watch_length);
        for (i = 0; i < watch_length; i++) {
                if (*p >= 0x20 && *p < 0x7f) {
                        printf(" %c",*p++ & 0xff);
                } else {
                        printf(" %02x",*p++ & 0xff);
                }
        }
        printf("\n");

}