#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  colormap; scalar_t__ border_pixel; } ;
typedef  TYPE_1__ XSetWindowAttributes ;
struct TYPE_9__ {int /*<<< orphan*/  visual; int /*<<< orphan*/  depth; int /*<<< orphan*/  screen; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  wnd; int /*<<< orphan*/ * dpy; TYPE_3__* vi; int /*<<< orphan*/  cmap; } ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_2__ GLContext ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 int CWBorderPixel ; 
 int CWColormap ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 int GLX_DOUBLEBUFFER ; 
 int GLX_RGBA ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  InputOutput ; 
 int None ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XCreateColormap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display ; 
 TYPE_3__* glXChooseVisual (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * glXCreateContext (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glXQueryExtension (int /*<<< orphan*/ *,int*,int*) ; 

GLboolean CreateContext (GLContext* ctx)
{
  int attrib[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
  int erb, evb;
  XSetWindowAttributes swa;
  /* check input */
  if (NULL == ctx) return GL_TRUE;
  /* open display */
  ctx->dpy = XOpenDisplay(display);
  if (NULL == ctx->dpy) return GL_TRUE;
  /* query for glx */
  if (!glXQueryExtension(ctx->dpy, &erb, &evb)) return GL_TRUE;
  /* choose visual */
  ctx->vi = glXChooseVisual(ctx->dpy, DefaultScreen(ctx->dpy), attrib);
  if (NULL == ctx->vi) return GL_TRUE;
  /* create context */
  ctx->ctx = glXCreateContext(ctx->dpy, ctx->vi, None, True);
  if (NULL == ctx->ctx) return GL_TRUE;
  /* create window */
  /*wnd = XCreateSimpleWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 1, 1, 1, 0, 0);*/
  ctx->cmap = XCreateColormap(ctx->dpy, RootWindow(ctx->dpy, ctx->vi->screen),
                              ctx->vi->visual, AllocNone);
  swa.border_pixel = 0;
  swa.colormap = ctx->cmap;
  ctx->wnd = XCreateWindow(ctx->dpy, RootWindow(ctx->dpy, ctx->vi->screen), 
                           0, 0, 1, 1, 0, ctx->vi->depth, InputOutput, ctx->vi->visual, 
                           CWBorderPixel | CWColormap, &swa);
  /* make context current */
  if (!glXMakeCurrent(ctx->dpy, ctx->wnd, ctx->ctx)) return GL_TRUE;
  return GL_FALSE;
}