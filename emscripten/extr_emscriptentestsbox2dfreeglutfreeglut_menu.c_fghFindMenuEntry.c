#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ First; } ;
struct TYPE_10__ {TYPE_1__ Entries; } ;
struct TYPE_8__ {scalar_t__ Next; } ;
struct TYPE_9__ {TYPE_2__ Node; } ;
typedef  TYPE_3__ SFG_MenuEntry ;
typedef  TYPE_4__ SFG_Menu ;

/* Variables and functions */

__attribute__((used)) static SFG_MenuEntry *fghFindMenuEntry( SFG_Menu* menu, int index )
{
    SFG_MenuEntry *entry;
    int i = 1;

    for( entry = (SFG_MenuEntry *)menu->Entries.First;
         entry;
         entry = (SFG_MenuEntry *)entry->Node.Next )
    {
        if( i == index )
            break;
        ++i;
    }

    return entry;
}