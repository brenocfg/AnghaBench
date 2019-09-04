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
typedef  int IDATA ;

/* Variables and functions */
 int FD_BIAS ; 
 int errno ; 
 int /*<<< orphan*/  findError (int) ; 
 int hyerror_set_last_error (int,int /*<<< orphan*/ ) ; 
 int write (int,void const*,int) ; 

IDATA hyfile_write (IDATA fd, const void *buf, IDATA nbytes)
{
    IDATA rc = 0;
    
#ifdef ZOS
    if (fd == HYPORT_TTY_OUT) {
        rc = fwrite(buf, sizeof(char), nbytes, stdout);
    } else if (fd == HYPORT_TTY_ERR) {
        rc = fwrite(buf, sizeof(char), nbytes, stderr);
    } else if (fd < FD_BIAS) {
        /* Cannot fsync STDIN, and no other FD's should exist <FD_BIAS */
        return -1;
    } else 
#endif /* ZOS */
    {
        /* write will just do the right thing for HYPORT_TTY_OUT and HYPORT_TTY_ERR */
        rc = write ((int) (fd - FD_BIAS), buf, nbytes);
    }
    
    if (rc == -1)
    {
        int rc = errno;
        return hyerror_set_last_error(rc, findError(rc));
    }
    
    return rc;
}