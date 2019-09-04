#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* First; } ;
struct TYPE_12__ {int X; int Y; } ;
struct TYPE_11__ {int X; int Y; int /*<<< orphan*/  Use; } ;
struct TYPE_10__ {int X; int Y; void* Use; } ;
struct TYPE_15__ {int MajorVersion; int DisplayMode; int GameModeDepth; int GameModeRefresh; void* Initialised; TYPE_4__* ProgramName; scalar_t__ FPSInterval; scalar_t__ SwapTime; scalar_t__ SwapCount; scalar_t__ MenuStatusCallback; scalar_t__ MenuStateCallback; int /*<<< orphan*/ * IdleCallback; TYPE_8__ FreeTimers; TYPE_8__ Timers; TYPE_3__ GameModeSize; int /*<<< orphan*/  Modifiers; int /*<<< orphan*/  KeyRepeat; int /*<<< orphan*/  ExecState; int /*<<< orphan*/  ActionOnWindowClose; void* XSyncSwitch; void* GLDebugSwitch; void* UseCurrentContext; void* ForceIconic; int /*<<< orphan*/  DirectContext; TYPE_2__ Size; TYPE_1__ Position; scalar_t__ ContextProfile; scalar_t__ ContextFlags; scalar_t__ MinorVersion; void* InputDevsInitialised; void* JoysticksInitialised; } ;
struct TYPE_14__ {TYPE_4__* MenuContext; } ;
struct TYPE_13__ {int /*<<< orphan*/  Node; } ;
typedef  TYPE_4__ SFG_Timer ;
typedef  scalar_t__ FGCBMenuStatus ;
typedef  scalar_t__ FGCBMenuState ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_ACTION_EXIT ; 
 int GLUT_DEPTH ; 
 int /*<<< orphan*/  GLUT_EXEC_STATE_INIT ; 
 int /*<<< orphan*/  GLUT_KEY_REPEAT_ON ; 
 int GLUT_RGBA ; 
 int GLUT_SINGLE ; 
 int /*<<< orphan*/  GLUT_TRY_DIRECT_CONTEXT ; 
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  INVALID_MODIFIERS ; 
 int /*<<< orphan*/  fgDestroyStructure () ; 
 int /*<<< orphan*/  fgInputDeviceClose () ; 
 int /*<<< orphan*/  fgJoystickClose () ; 
 int /*<<< orphan*/  fgListInit (TYPE_8__*) ; 
 int /*<<< orphan*/  fgListRemove (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_7__ fgState ; 
 TYPE_6__ fgStructure ; 
 int /*<<< orphan*/  fgWarning (char*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 

void fgDeinitialize( void )
{
    SFG_Timer *timer;

    if( !fgState.Initialised )
    {
        fgWarning( "fgDeinitialize(): "
                   "no valid initialization has been performed" );
        return;
    }

    /* If there was a menu created, destroy the rendering context */
    if( fgStructure.MenuContext )
    {
#if TARGET_HOST_POSIX_X11
        /* Note that the MVisualInfo is not owned by the MenuContext! */
        glXDestroyContext( fgDisplay.Display, fgStructure.MenuContext->MContext );
#endif
        free( fgStructure.MenuContext );
        fgStructure.MenuContext = NULL;
    }

    fgDestroyStructure( );

    while( ( timer = fgState.Timers.First) )
    {
        fgListRemove( &fgState.Timers, &timer->Node );
        free( timer );
    }

    while( ( timer = fgState.FreeTimers.First) )
    {
        fgListRemove( &fgState.FreeTimers, &timer->Node );
        free( timer );
    }

#if !defined(_WIN32_WCE)
    if ( fgState.JoysticksInitialised )
        fgJoystickClose( );

    if ( fgState.InputDevsInitialised )
        fgInputDeviceClose( );
#endif /* !defined(_WIN32_WCE) */
    fgState.JoysticksInitialised = GL_FALSE;
    fgState.InputDevsInitialised = GL_FALSE;

    fgState.MajorVersion = 1;
    fgState.MinorVersion = 0;
    fgState.ContextFlags = 0;
    fgState.ContextProfile = 0;

    fgState.Initialised = GL_FALSE;

    fgState.Position.X = -1;
    fgState.Position.Y = -1;
    fgState.Position.Use = GL_FALSE;

    fgState.Size.X = 300;
    fgState.Size.Y = 300;
    fgState.Size.Use = GL_TRUE;

    fgState.DisplayMode = GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH;

    fgState.DirectContext  = GLUT_TRY_DIRECT_CONTEXT;
    fgState.ForceIconic         = GL_FALSE;
    fgState.UseCurrentContext   = GL_FALSE;
    fgState.GLDebugSwitch       = GL_FALSE;
    fgState.XSyncSwitch         = GL_FALSE;
    fgState.ActionOnWindowClose = GLUT_ACTION_EXIT;
    fgState.ExecState           = GLUT_EXEC_STATE_INIT;

    fgState.KeyRepeat       = GLUT_KEY_REPEAT_ON;
    fgState.Modifiers       = INVALID_MODIFIERS;

    fgState.GameModeSize.X  = 640;
    fgState.GameModeSize.Y  = 480;
    fgState.GameModeDepth   =  16;
    fgState.GameModeRefresh =  72;

    fgListInit( &fgState.Timers );
    fgListInit( &fgState.FreeTimers );

    fgState.IdleCallback = NULL;
    fgState.MenuStateCallback = ( FGCBMenuState )NULL;
    fgState.MenuStatusCallback = ( FGCBMenuStatus )NULL;

    fgState.SwapCount   = 0;
    fgState.SwapTime    = 0;
    fgState.FPSInterval = 0;

    if( fgState.ProgramName )
    {
        free( fgState.ProgramName );
        fgState.ProgramName = NULL;
    }

#if TARGET_HOST_POSIX_X11

    /*
     * Make sure all X-client data we have created will be destroyed on
     * display closing
     */
    XSetCloseDownMode( fgDisplay.Display, DestroyAll );

    /*
     * Close the display connection, destroying all windows we have
     * created so far
     */
    XCloseDisplay( fgDisplay.Display );

#elif TARGET_HOST_MS_WINDOWS

    /* Reset the timer granularity */
    timeEndPeriod ( 1 );

#endif

    fgState.Initialised = GL_FALSE;
}