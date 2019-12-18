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
 int /*<<< orphan*/  FSA_REF_SD ; 
 int IOSUHAX_FSA_RawOpen (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_fsa_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_fsa_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsaFdSd ; 
 int sdioFd ; 

__attribute__((used)) static bool IOSUHAX_sdio_startup(void)
{
    if(!IOSUHAX_disc_io_fsa_open(FSA_REF_SD))
        return false;

    if(sdioFd < 0)
    {
        int res = IOSUHAX_FSA_RawOpen(fsaFdSd, "/dev/sdcard01", &sdioFd);
        if(res < 0)
        {
            IOSUHAX_disc_io_fsa_close(FSA_REF_SD);
            sdioFd = -1;
        }
    }

    return (sdioFd >= 0);
}