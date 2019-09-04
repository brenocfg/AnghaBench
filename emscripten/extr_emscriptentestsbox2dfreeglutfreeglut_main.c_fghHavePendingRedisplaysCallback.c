#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* data; int /*<<< orphan*/  found; } ;
struct TYPE_10__ {scalar_t__ Visible; scalar_t__ Redisplay; } ;
struct TYPE_11__ {TYPE_1__ State; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  TYPE_3__ SFG_Enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  fgEnumSubWindows (TYPE_2__*,void (*) (TYPE_2__*,TYPE_3__*),TYPE_3__*) ; 

__attribute__((used)) static void fghHavePendingRedisplaysCallback( SFG_Window* w, SFG_Enumerator* e)
{
    if( w->State.Redisplay && w->State.Visible )
    {
        e->found = GL_TRUE;
        e->data = w;
    }
    fgEnumSubWindows( w, fghHavePendingRedisplaysCallback, e );
}