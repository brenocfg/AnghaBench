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
 int /*<<< orphan*/  IOSUHAX_FSA_RawClose (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_fsa_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOSUHAX_sdio_isInserted () ; 
 int /*<<< orphan*/  fsaFdSd ; 
 int sdioFd ; 

__attribute__((used)) static bool IOSUHAX_sdio_shutdown(void)
{
    if(!IOSUHAX_sdio_isInserted())
        return false;

    IOSUHAX_FSA_RawClose(fsaFdSd, sdioFd);
    IOSUHAX_disc_io_fsa_close(FSA_REF_SD);
    sdioFd = -1;
    return true;
}