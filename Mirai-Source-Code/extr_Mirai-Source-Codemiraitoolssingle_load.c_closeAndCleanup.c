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
struct linger {int l_onoff; scalar_t__ l_linger; } ;
typedef  int /*<<< orphan*/  linger ;
struct TYPE_2__ {int fd; scalar_t__ is_open; scalar_t__ got_prompt; scalar_t__ special; scalar_t__ success; scalar_t__ pathInd; scalar_t__ echoInd; scalar_t__* password; scalar_t__* username; scalar_t__** path; scalar_t__ state; scalar_t__ slotUsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* stateTable ; 

void closeAndCleanup(int fd)
{
    if(stateTable[fd].slotUsed && stateTable[fd].fd == fd)
    {
        stateTable[fd].slotUsed = 0;
        stateTable[fd].state = 0;
        stateTable[fd].path[0][0] = 0;
        stateTable[fd].path[1][0] = 0;
        stateTable[fd].path[2][0] = 0;
        stateTable[fd].path[3][0] = 0;
        stateTable[fd].path[4][0] = 0;
        stateTable[fd].username[0] = 0;
        stateTable[fd].password[0] = 0;
        stateTable[fd].echoInd = 0;
        stateTable[fd].pathInd = 0;
        stateTable[fd].success = 0;
        stateTable[fd].special = 0;
        stateTable[fd].got_prompt = 0;
    
        if(stateTable[fd].is_open)
        {
            stateTable[fd].is_open = 0;
            
            shutdown(fd, SHUT_RDWR);
            struct linger linger;
            linger.l_onoff = 1;
            linger.l_linger = 0;
            setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &linger, sizeof(linger));
            close(fd);
        }
    }
}