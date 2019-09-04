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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Windows; scalar_t__ WindowID; } ;
struct TYPE_8__ {int OldHeight; int OldWidth; void* IsFullscreen; void* KeyRepeating; void* IgnoreKeyRepeat; int /*<<< orphan*/  Cursor; } ;
struct TYPE_9__ {TYPE_1__ State; int /*<<< orphan*/  IsMenu; int /*<<< orphan*/  Node; struct TYPE_9__* Parent; int /*<<< orphan*/  Children; scalar_t__ ID; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_CURSOR_INHERIT ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fgListAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgListInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgOpenWindow (TYPE_2__*,char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ fgStructure ; 
 int /*<<< orphan*/  fghClearCallBacks (TYPE_2__*) ; 

SFG_Window* fgCreateWindow( SFG_Window* parent, const char* title,
                            GLboolean positionUse, int x, int y,
                            GLboolean sizeUse, int w, int h,
                            GLboolean gameMode, GLboolean isMenu )
{
    /* Have the window object created */
    SFG_Window *window = (SFG_Window *)calloc( sizeof(SFG_Window), 1 );

#if TARGET_HOST_UNIX_X11
    window->Window.FBConfig = NULL;
#endif
    fghClearCallBacks( window );

    /* Initialize the object properties */
    window->ID = ++fgStructure.WindowID;
    window->State.OldHeight = window->State.OldWidth = -1;

    fgListInit( &window->Children );
    if( parent )
    {
        fgListAppend( &parent->Children, &window->Node );
        window->Parent = parent;
    }
    else
        fgListAppend( &fgStructure.Windows, &window->Node );

    /* Set the default mouse cursor and reset the modifiers value */
    window->State.Cursor    = GLUT_CURSOR_INHERIT;

    window->IsMenu = isMenu;

    window->State.IgnoreKeyRepeat = GL_FALSE;
    window->State.KeyRepeating    = GL_FALSE;
    window->State.IsFullscreen    = GL_FALSE;

    /*
     * Open the window now. The fgOpenWindow() function is system
     * dependant, and resides in freeglut_window.c. Uses fgState.
     */
    fgOpenWindow( window, title, positionUse, x, y, sizeUse, w, h, gameMode,
                  (GLboolean)(parent ? GL_TRUE : GL_FALSE) );

    return window;
}