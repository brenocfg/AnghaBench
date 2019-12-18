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
 scalar_t__ debug_mode ; 
 int /*<<< orphan*/  hexDump (char*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int recv (int,void*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 TYPE_1__* stateTable ; 

int log_recv(int sock, void *buf, int len, int flags)
{
    memset(buf, 0, len);
    int ret = recv(sock, buf, len, flags);
    if (ret > 0)
    {
        int i = 0;
        for(i = 0; i < ret; i++)
        {
            if (((char *)buf)[i] == 0x00)
            {
                ((char *)buf)[i] = 'A';
            }
        }
    }
    if (debug_mode)
    {
        char hex_buf[32] = {0};
        sprintf(hex_buf, "state %d - recv: %d", stateTable[sock].state, ret);
        if (ret != -1)
            hexDump(hex_buf, buf, ret);
        else
            printf("%s\n", hex_buf);
    }
    return ret;
        
}