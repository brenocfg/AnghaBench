#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ First; } ;
struct TYPE_15__ {TYPE_1__ Windows; } ;
struct TYPE_14__ {scalar_t__ found; } ;
struct TYPE_12__ {scalar_t__ Next; } ;
struct TYPE_13__ {TYPE_2__ Node; } ;
typedef  TYPE_3__ SFG_Window ;
typedef  TYPE_4__ SFG_Enumerator ;
typedef  int /*<<< orphan*/  (* FGCBenumerator ) (TYPE_3__*,TYPE_4__*) ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_INTERNAL_ERROR_EXIT (int,char*,char*) ; 
 TYPE_7__ fgStructure ; 

void fgEnumWindows( FGCBenumerator enumCallback, SFG_Enumerator* enumerator )
{
    SFG_Window *window;

    FREEGLUT_INTERNAL_ERROR_EXIT ( enumCallback && enumerator,
                                   "Enumerator or callback missing from window enumerator call",
                                   "fgEnumWindows" );

    /* Check every of the top-level windows */
    for( window = ( SFG_Window * )fgStructure.Windows.First;
         window;
         window = ( SFG_Window * )window->Node.Next )
    {
        enumCallback( window, enumerator );
        if( enumerator->found )
            return;
    }
}