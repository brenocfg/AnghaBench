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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int I_32 ;
typedef  int IDATA ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int EsTranslateOpenFlags (int) ; 
 scalar_t__ FD_BIAS ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int HyOpenRead ; 
 int HyOpenWrite ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  findError (int) ; 
 int /*<<< orphan*/  hyerror_set_last_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hyerror_set_last_error_with_message (int /*<<< orphan*/ ,char*) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

IDATA hyfile_open (const char *path, I_32 flags, I_32 mode)
{
    struct stat buffer;
    I_32 fd;
    I_32 realFlags = EsTranslateOpenFlags (flags);
    I_32 fdflags;
    
    // Trc_PRT_file_open_Entry (path, flags, mode);
    
    if (realFlags == -1)
    {
        // Trc_PRT_file_open_Exit1 (flags);
        hyerror_set_last_error(EINVAL, findError(EINVAL));
        return -1;
    }
    
    if ( ( flags&HyOpenRead && !(flags&HyOpenWrite) )  && !stat (path, &buffer))
    {
        if (S_ISDIR (buffer.st_mode))
        {
            hyerror_set_last_error_with_message(findError(EEXIST), "Is a directory");
            // Trc_PRT_file_open_Exit4 ();
            return -1;
        }
    }
    
    fd = open (path, realFlags, mode);
    
    if (-1 == fd)
    {
        // Trc_PRT_file_open_Exit2 (errno, findError (errno));
        int rc = errno;
        hyerror_set_last_error(rc, findError(rc));
        return -1;
    }
    
    /* Tag this descriptor as being non-inheritable */
    fdflags = fcntl (fd, F_GETFD, 0);
    fcntl (fd, F_SETFD, fdflags | FD_CLOEXEC);
    
    fd += FD_BIAS;
    // Trc_PRT_file_open_Exit (fd);
    return (IDATA) fd;
}