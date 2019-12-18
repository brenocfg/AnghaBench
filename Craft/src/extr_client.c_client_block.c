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
 int /*<<< orphan*/  client_enabled ; 
 int /*<<< orphan*/  client_send (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

void client_block(int x, int y, int z, int w) {
    if (!client_enabled) {
        return;
    }
    char buffer[1024];
    snprintf(buffer, 1024, "B,%d,%d,%d,%d\n", x, y, z, w);
    client_send(buffer);
}