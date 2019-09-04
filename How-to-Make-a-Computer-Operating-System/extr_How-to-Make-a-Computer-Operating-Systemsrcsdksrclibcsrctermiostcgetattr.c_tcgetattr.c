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
struct termios {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCGETA ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct termios*) ; 

int tcgetattr( int fd, struct termios* tio ) {
    int error;

    if ( tio == NULL ) {
        errno = EINVAL;
        return -1;
    }

    error = ioctl( fd, TCGETA, tio );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}