#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dpy; } ;
typedef  int /*<<< orphan*/  GLXFBConfig ;
typedef  TYPE_1__ GLContext ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 scalar_t__ GLXEW_NV_float_buffer ; 
 int GLX_ACCUM_ALPHA_SIZE ; 
 int GLX_ACCUM_BLUE_SIZE ; 
 int GLX_ACCUM_GREEN_SIZE ; 
 int GLX_ACCUM_RED_SIZE ; 
 int GLX_ALPHA_SIZE ; 
 int GLX_AUX_BUFFERS ; 
 int GLX_BLUE_SIZE ; 
 int GLX_BUFFER_SIZE ; 
 int GLX_COLOR_INDEX_BIT ; 
 int GLX_CONFIG_CAVEAT ; 
 int GLX_DEPTH_SIZE ; 
 int GLX_DIRECT_COLOR ; 
 int GLX_DOUBLEBUFFER ; 
 int GLX_DRAWABLE_TYPE ; 
 int GLX_FBCONFIG_ID ; 
 int GLX_FLOAT_COMPONENTS_NV ; 
 int GLX_GRAY_SCALE ; 
 int GLX_GREEN_SIZE ; 
 int GLX_LEVEL ; 
 int GLX_NONE ; 
 int GLX_NON_CONFORMANT_CONFIG ; 
 int GLX_PBUFFER_BIT ; 
 int GLX_PIXMAP_BIT ; 
 int GLX_PSEUDO_COLOR ; 
 int GLX_RED_SIZE ; 
 int GLX_RENDER_TYPE ; 
 int GLX_RGBA_BIT ; 
 int GLX_RGBA_FLOAT_ATI_BIT ; 
 int GLX_SAMPLES ; 
 int GLX_SAMPLE_BUFFERS ; 
 int GLX_SLOW_CONFIG ; 
 int GLX_STATIC_COLOR ; 
 int GLX_STATIC_GRAY ; 
 int GLX_STENCIL_SIZE ; 
 int GLX_STEREO ; 
 int GLX_TRANSPARENT_INDEX ; 
 int GLX_TRANSPARENT_RGB ; 
 int GLX_TRANSPARENT_TYPE ; 
 int GLX_TRUE_COLOR ; 
 int GLX_WINDOW_BIT ; 
 int GLX_X_RENDERABLE ; 
 int GLX_X_VISUAL_TYPE ; 
 int GL_TRUE ; 
 int Success ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int glXGetFBConfigAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/ * glXGetFBConfigs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  verbose ; 

void
VisualInfo (GLContext* ctx)
{
  int n_fbc;
  GLXFBConfig* fbc;
  int value, ret, i;

  fbc = glXGetFBConfigs(ctx->dpy, DefaultScreen(ctx->dpy), &n_fbc);

  if (fbc)
  {
    if (!verbose)
    {
      /* print table header */
      fprintf(file, " +-----+-------------------------+-----------------+----------+-------------+-------+------+\n");
      fprintf(file, " |     |        visual           |      color      | ax dp st |    accum    |   ms  |  cav |\n");
      fprintf(file, " |  id | tp xr cl fm db st lv xp |  sz  r  g  b  a | bf th cl | r  g  b  a  | ns  b |  eat |\n");
      fprintf(file, " +-----+-------------------------+-----------------+----------+-------------+-------+------+\n");
      /* loop through all the fbcs */
      for (i=0; i<n_fbc; i++)
      {
        /* print out the information for this fbc */
        /* visual id */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_FBCONFIG_ID, &value);
        if (ret != Success)
        {
          fprintf(file, "|  ?  |");
        }
        else
        {
          fprintf(file, " |% 4d | ", value);
        }
        /* visual type */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_DRAWABLE_TYPE, &value);
        if (ret != Success)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value & GLX_WINDOW_BIT)
          {
            if (value & GLX_PBUFFER_BIT)
            {
              fprintf(file, "wp ");
            }
            else
            {
              fprintf(file, "wn ");
            }
          }
          else
          {
            if (value & GLX_PBUFFER_BIT)
            {
              fprintf(file, "pb ");
            }
            else if (value & GLX_PIXMAP_BIT)
            {
              fprintf(file, "pm ");
            }
            else
            {
              fprintf(file, " ? ");
            }
          }
        }
        /* x renderable */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_X_RENDERABLE, &value);
        if (ret != Success)
        {
          fprintf(file, " ? ");
        }
        else
        {
          fprintf(file, value ? " y " : " n ");
        }
        /* class */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_X_VISUAL_TYPE, &value);
        if (ret != Success)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (GLX_TRUE_COLOR == value)
            fprintf(file, "tc ");
          else if (GLX_DIRECT_COLOR == value)
            fprintf(file, "dc ");
          else if (GLX_PSEUDO_COLOR == value)
            fprintf(file, "pc ");
          else if (GLX_STATIC_COLOR == value)
            fprintf(file, "sc ");
          else if (GLX_GRAY_SCALE == value)
            fprintf(file, "gs ");
          else if (GLX_STATIC_GRAY == value)
            fprintf(file, "sg ");
          else if (GLX_X_VISUAL_TYPE == value)
            fprintf(file, " . ");
          else
            fprintf(file, " ? ");
        }
        /* format */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_RENDER_TYPE, &value);
        if (ret != Success)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (GLXEW_NV_float_buffer)
          {
            int ret2, value2;
            ret2 = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_FLOAT_COMPONENTS_NV, &value2);
            if (Success == ret2 && GL_TRUE == value2)
            {
              fprintf(file, " f ");
            }
            else if (value & GLX_RGBA_BIT)
              fprintf(file, " i ");
            else if (value & GLX_COLOR_INDEX_BIT)
              fprintf(file, " c ");
            else
              fprintf(file, " ? ");
          }
          else
          {
            if (value & GLX_RGBA_FLOAT_ATI_BIT)
              fprintf(file, " f ");
            else if (value & GLX_RGBA_BIT)
              fprintf(file, " i ");
            else if (value & GLX_COLOR_INDEX_BIT)
              fprintf(file, " c ");
            else
              fprintf(file, " ? ");
          }
        }
        /* double buffer */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_DOUBLEBUFFER, &value);
        fprintf(file, " %c ", Success != ret ? '?' : (value ? 'y' : '.'));
        /* stereo */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_STEREO, &value);
        fprintf(file, " %c ", Success != ret ? '?' : (value ? 'y' : '.'));
        /* level */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_LEVEL, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          fprintf(file, "%2d ", value);
        }
        /* transparency */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_TRANSPARENT_TYPE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? | ");
        }
        else
        {
          if (GLX_TRANSPARENT_RGB == value)
            fprintf(file, " r | ");
          else if (GLX_TRANSPARENT_INDEX == value)
            fprintf(file, " i | ");
          else if (GLX_NONE == value)
            fprintf(file, " . | ");
          else
            fprintf(file, " ? | ");
        }
        /* color size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_BUFFER_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, "  ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%3d ", value);
          else
            fprintf(file, "  . ");
        }
        /* red size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_RED_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* green size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_GREEN_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* blue size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_BLUE_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* alpha size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_ALPHA_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? | ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d | ", value);
          else
            fprintf(file, " . | ");
        }
        /* aux buffers */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_AUX_BUFFERS, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* depth size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_DEPTH_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* stencil size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_STENCIL_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? | ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d | ", value);
          else
            fprintf(file, " . | ");
        }
        /* accum red size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_ACCUM_RED_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* accum green size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_ACCUM_GREEN_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* accum blue size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_ACCUM_BLUE_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d ", value);
          else
            fprintf(file, " . ");
        }
        /* accum alpha size */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_ACCUM_ALPHA_SIZE, &value);
        if (Success != ret)
        {
          fprintf(file, " ? | ");
        }
        else
        {
          if (value)
            fprintf(file, "%2d | ", value);
          else
            fprintf(file, " . | ");
        }
        /* multisample */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_SAMPLES, &value);
        if (Success != ret)
        {
          fprintf(file, " ? ");
        }
        else
        {
          fprintf(file, "%2d ", value);
        }
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_SAMPLE_BUFFERS, &value);
        if (Success != ret)
        {
          fprintf(file, " ? | ");
        }
        else
        {
          fprintf(file, "%2d | ", value);
        }
        /* caveat */
        ret = glXGetFBConfigAttrib(ctx->dpy, fbc[i], GLX_CONFIG_CAVEAT, &value);
        if (Success != ret)
        {
          fprintf(file, "???? |");
        }
        else
        {
          if (GLX_NONE == value)
            fprintf(file, "none |\n");
          else if (GLX_SLOW_CONFIG == value)
            fprintf(file, "slow |\n");
          else if (GLX_NON_CONFORMANT_CONFIG == value)
            fprintf(file, "ncft |\n");
          else
            fprintf(file, "???? |\n");
        }
      }
      /* print table footer */
      fprintf(file, " +-----+-------------------------+-----------------+----------+-------------+-------+------+\n");
      fprintf(file, " |  id | tp xr cl fm db st lv xp |  sz  r  g  b  a | bf th cl | r  g  b  a  | ns  b |  eat |\n");
      fprintf(file, " |     |        visual           |      color      | ax dp st |    accum    |   ms  |  cav |\n");
      fprintf(file, " +-----+-------------------------+-----------------+----------+-------------+-------+------+\n");
    }
  }
}