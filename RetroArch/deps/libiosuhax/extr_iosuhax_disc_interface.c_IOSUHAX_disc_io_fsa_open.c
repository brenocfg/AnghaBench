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
 int FSA_REF_SD ; 
 int FSA_REF_USB ; 
 scalar_t__ IOSUHAX_FSA_Open () ; 
 scalar_t__ IOSUHAX_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOSUHAX_disc_io_initialize () ; 
 scalar_t__ fsaFdSd ; 
 scalar_t__ fsaFdUsb ; 

__attribute__((used)) static bool IOSUHAX_disc_io_fsa_open(int fsaFd)
{
    IOSUHAX_disc_io_initialize();

    if(IOSUHAX_Open(NULL) < 0)
        return false;

    if(fsaFd == FSA_REF_SD)
    {
        if(fsaFdSd < 0)
        {
            fsaFdSd = IOSUHAX_FSA_Open();
        }

        if(fsaFdSd >= 0)
            return true;
    }
    else if(fsaFd == FSA_REF_USB)
    {
        if(fsaFdUsb < 0)
        {
            fsaFdUsb = IOSUHAX_FSA_Open();
        }

        if(fsaFdUsb >= 0)
            return true;
    }

    return false;
}