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
struct proc {TYPE_1__* p_fd; } ;
struct TYPE_2__ {int* fd_ofileflags; } ;

/* Variables and functions */
 int UF_CLOSING ; 
 int UF_RESERVED ; 

void
procfdtbl_markclosefd(struct proc * p, int fd)
{
        p->p_fd->fd_ofileflags[fd] |= (UF_RESERVED | UF_CLOSING);
}