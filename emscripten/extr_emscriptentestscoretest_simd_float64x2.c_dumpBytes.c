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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void dumpBytes(const char *name, const void *bytes, int n)
{
    printf("%s:", name);
    for(int i = 0; i < n; ++i)
        printf(" %02X", ((uint8_t*)bytes)[i]);
    printf("\n");
}