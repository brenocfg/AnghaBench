#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * Display; } ;
struct TYPE_10__ {int DisplayMode; scalar_t__ DirectContext; } ;
struct TYPE_9__ {int /*<<< orphan*/  MenuContext; } ;
struct TYPE_7__ {int /*<<< orphan*/ * FBConfig; } ;
struct TYPE_8__ {TYPE_1__ Window; scalar_t__ IsMenu; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  int /*<<< orphan*/  GLXFBConfig ;
typedef  int /*<<< orphan*/ * GLXContext ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/ * (* CreateContextAttribsProc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ;
typedef  int Bool ;

/* Variables and functions */
 scalar_t__ GLUT_FORCE_INDIRECT_CONTEXT ; 
 int GLUT_INDEX ; 
 int GLX_COLOR_INDEX_TYPE ; 
 int GLX_RGBA_TYPE ; 
 TYPE_6__ fgDisplay ; 
 int /*<<< orphan*/  fgError (char*) ; 
 TYPE_5__ fgState ; 
 TYPE_4__ fgStructure ; 
 int /*<<< orphan*/  fgWarning (char*) ; 
 int /*<<< orphan*/  fghContextCreationError () ; 
 int /*<<< orphan*/  fghFillContextAttributes (int*) ; 
 scalar_t__ fghGetProcAddress (char*) ; 
 scalar_t__ fghIsLegacyContextRequested () ; 
 int /*<<< orphan*/ * glXCreateNewContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static GLXContext fghCreateNewContext( SFG_Window* window )
{
  /* for color model calculation */
  int menu = ( window->IsMenu && !fgStructure.MenuContext );
  int index_mode = ( fgState.DisplayMode & GLUT_INDEX );

  /* "classic" context creation */
  Display *dpy = fgDisplay.Display;
  GLXFBConfig config = *(window->Window.FBConfig);
  int render_type = ( !menu && index_mode ) ? GLX_COLOR_INDEX_TYPE : GLX_RGBA_TYPE;
  GLXContext share_list = NULL;
  Bool direct = ( fgState.DirectContext != GLUT_FORCE_INDIRECT_CONTEXT );
  GLXContext context;

  /* new context creation */
  int attributes[9];
  CreateContextAttribsProc createContextAttribs;

  /* If nothing fancy has been required, simply use the old context creation GLX API entry */
  if ( fghIsLegacyContextRequested() )
  {
    context = glXCreateNewContext( dpy, config, render_type, share_list, direct );
    if ( context == NULL ) {
      fghContextCreationError();
    }
    return context;
  }

  /* color index mode is not available anymore with OpenGL 3.0 */
  if ( render_type == GLX_COLOR_INDEX_TYPE ) {
    fgWarning( "color index mode is deprecated, using RGBA mode" );
  }

  fghFillContextAttributes( attributes );

  createContextAttribs = (CreateContextAttribsProc) fghGetProcAddress( "glXCreateContextAttribsARB" );
  if ( createContextAttribs == NULL ) {
    fgError( "glXCreateContextAttribsARB not found" );
  }

  context = createContextAttribs( dpy, config, share_list, direct, attributes );
  if ( context == NULL ) {
    fghContextCreationError();
  }
  return context;
}