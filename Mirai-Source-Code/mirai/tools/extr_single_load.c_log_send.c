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
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int bytes_sent ; 
 scalar_t__ debug_mode ; 
 int /*<<< orphan*/  hexDump (char*,void*,int) ; 
 int send (int,void*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 TYPE_1__* stateTable ; 

int log_send(int sock, void *buf, int len, int flags)
{
    if (debug_mode)
    {
        char hex_buf[32] = {0};
        sprintf(hex_buf, "state %d - send: %d", stateTable[sock].state, len);
        hexDump(hex_buf, buf, len);
    }
    bytes_sent+=len;
    return send(sock, buf, len, flags);
}