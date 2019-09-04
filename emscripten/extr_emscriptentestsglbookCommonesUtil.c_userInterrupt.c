#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  xkey; } ;
typedef  TYPE_1__ XEvent ;
struct TYPE_7__ {int /*<<< orphan*/  (* keyFunc ) (TYPE_2__*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  KeySym ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 scalar_t__ DestroyNotify ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ KeyPress ; 
 int XLookupString (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ XPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_display ; 

GLboolean userInterrupt(ESContext *esContext)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while ( XPending ( x_display ) )
    {
        XNextEvent( x_display, &xev );
        if ( xev.type == KeyPress )
        {
            if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
            {
                if (esContext->keyFunc != NULL)
                    esContext->keyFunc(esContext, text, 0, 0);
            }
        }
        if ( xev.type == DestroyNotify )
            userinterrupt = GL_TRUE;
    }
    return userinterrupt;
}