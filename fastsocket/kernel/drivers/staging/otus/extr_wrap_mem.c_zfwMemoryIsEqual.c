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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8_t zfwMemoryIsEqual(u8_t* m1, u8_t* m2, u16_t length)
{
    //u16_t i;
    int ret;

    ret = memcmp(m1, m2, length);

    return ((ret==0)?TRUE:FALSE);
    //for(i=0; i<length; i++)
    //{
    //    if ( m1[i] != m2[i] )
    //    {
    //        return FALSE;
    //    }
    //}

    //return TRUE;
}