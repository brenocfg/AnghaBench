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
 scalar_t__ DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA_BUSY_REG ; 

void esp_sha_wait_idle(void)
{
    while(DPORT_REG_READ(SHA_BUSY_REG) != 0) { }
}