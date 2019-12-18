#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  retransmitfrom; } ;
typedef  TYPE_1__ doomdata_t ;
struct TYPE_4__ {int /*<<< orphan*/  retransmitfrom; } ;

/* Variables and functions */
 unsigned int NCMD_CHECKSUM ; 
 int NetbufferSize () ; 
 TYPE_2__* netbuffer ; 

unsigned NetbufferChecksum (void)
{
    unsigned		c;
    int		i,l;

    c = 0x1234567;

    // FIXME -endianess?
#ifdef NORMALUNIX
    return 0;			// byte order problems
#endif

    l = (NetbufferSize () - (int)&(((doomdata_t *)0)->retransmitfrom))/4;
    for (i=0 ; i<l ; i++)
	c += ((unsigned *)&netbuffer->retransmitfrom)[i] * (i+1);

    return c & NCMD_CHECKSUM;
}