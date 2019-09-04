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
struct uuid_command {void* uuid; } ;
typedef  int /*<<< orphan*/  kernel_mach_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_UUID ; 
 scalar_t__ getcommandfromheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *
getuuidfromheader(kernel_mach_header_t *mhp, unsigned long *size)
{
    struct uuid_command *cmd = (struct uuid_command *)
        getcommandfromheader(mhp, LC_UUID);

    if (cmd != NULL) {
        if (size) {
            *size = sizeof(cmd->uuid);
        }
        return cmd->uuid;
    }

    return NULL;
}