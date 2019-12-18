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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vc_hostfs_setend(int filedes)
{
    off_t   currPosn;

    if (( currPosn = lseek( filedes, 0, SEEK_CUR )) != (off_t)-1 )
    {
        if ( ftruncate( filedes, currPosn ) == 0 )
        {
            return 0;
        }
    }
   return -1;
}