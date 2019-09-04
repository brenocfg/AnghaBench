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
typedef  scalar_t__ IDATA ;

/* Variables and functions */
 scalar_t__ FD_BIAS ; 
 scalar_t__ read (int,void*,scalar_t__) ; 

IDATA hyfile_read (IDATA fd, void *buf, IDATA nbytes)
{
    IDATA result;
    if (nbytes == 0)
    {
        return 0;
    }
    
#ifdef ZOS
    if (fd == HYPORT_TTY_IN) {
        result = fread(buf, sizeof(char), nbytes, stdin);
    }  else	if (fd < FD_BIAS) {
        /* Cannot read from STDOUT/ERR, and no other FD's should exist <FD_BIAS */
        return -1;
    } else
#endif /* ZOS */
    {
        result = read ((int) (fd - FD_BIAS), buf, nbytes);
    }
    
    if (result == 0)
    {
        return -1;
    }
    else
    {
        return result;
    }
}