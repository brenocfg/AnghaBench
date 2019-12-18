#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s_write {TYPE_1__* data608; } ;
struct TYPE_2__ {int channel; } ;

/* Variables and functions */
 scalar_t__ debug_608 ; 
 int /*<<< orphan*/  hb_log (char*) ; 

__attribute__((used)) static int check_channel(unsigned char c1, struct s_write *wb)
{
    if (c1==0x14)
    {
        if (debug_608 && wb->data608->channel!=1)
            hb_log ("\nChannel change, now 1\n");
        return 1;
    }
    if (c1==0x1c)
    {
        if (debug_608 && wb->data608->channel!=2)
            hb_log ("\nChannel change, now 2\n");
        return 2;
    }
    if (c1==0x15)
    {
        if (debug_608 && wb->data608->channel!=3)
            hb_log ("\nChannel change, now 3\n");
        return 3;
    }
    if (c1==0x1d)
    {
        if (debug_608 && wb->data608->channel!=4)
            hb_log ("\nChannel change, now 4\n");
        return 4;
    }

    // Otherwise keep the current channel
    return wb->data608->channel;
}