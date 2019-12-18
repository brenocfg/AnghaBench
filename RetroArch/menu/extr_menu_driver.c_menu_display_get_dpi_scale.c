#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float menu_scale_factor; } ;
struct TYPE_7__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {float* value; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ gfx_ctx_metrics_t ;

/* Variables and functions */
 float DIAGONAL_PIXELS_1080P ; 
 int /*<<< orphan*/  DISPLAY_METRIC_DPI ; 
 float REFERENCE_DPI ; 
 TYPE_2__* config_get_ptr () ; 
 scalar_t__ sqrt (double) ; 
 scalar_t__ video_context_driver_get_metrics (TYPE_3__*) ; 

float menu_display_get_dpi_scale(unsigned width, unsigned height)
{
   static unsigned last_width  = 0;
   static unsigned last_height = 0;
   static float scale          = 0.0f;
   static bool scale_cached    = false;
   settings_t *settings        = config_get_ptr();

   /* Scale is based on display metrics - these are a fixed
    * hardware property. To minimise performance overheads
    * we therefore only call video_context_driver_get_metrics()
    * on first run, or when the current video resolution changes */
   if (!scale_cached ||
       (width  != last_width) ||
       (height != last_height))
   {
      float diagonal_pixels;
      float pixel_scale;
      float dpi;
      gfx_ctx_metrics_t metrics;

      /* Determine the diagonal 'size' of the display
       * (or window) in terms of pixels */
      diagonal_pixels = (float)sqrt(
            (double)((width * width) + (height * height)));

      /* TODO/FIXME: On Mac, calling video_context_driver_get_metrics()
       * here causes RetroArch to crash (EXC_BAD_ACCESS). This is
       * unfortunate, and needs to be fixed at the gfx context driver
       * level. Until this is done, all we can do is fallback to using
       * the old legacy 'magic number' scaling on Mac platforms.
       * Note: We use a rather ugly construct here so the 'Mac hack'
       * can be added in one place, without polluting the rest of
       * the code. */
#if defined(HAVE_COCOA) || defined(HAVE_COCOA_METAL)
      if (true)
      {
         scale        = (diagonal_pixels / 6.5f) / 212.0f;
         scale_cached = true;
         last_width   = width;
         last_height  = height;

         if (settings)
            return scale * ((settings->floats.menu_scale_factor > 0.0001f) ?
                  settings->floats.menu_scale_factor : 1.0f);

         return scale;
      }
#endif

      /* Get pixel scale relative to baseline 1080p display */
      pixel_scale = diagonal_pixels / DIAGONAL_PIXELS_1080P;

      /* Attempt to get display DPI */
      metrics.type  = DISPLAY_METRIC_DPI;
      metrics.value = &dpi;

      if (video_context_driver_get_metrics(&metrics) && (dpi > 0.0f))
      {
         float display_size;
         float dpi_scale;

#if defined(ANDROID) || defined(HAVE_COCOATOUCH)
         /* Android/iOS devices tell complete lies when
          * reporting DPI values. From the Android devices
          * I've had access to, the DPI is generally
          * overestimated by 17%. All we can do is apply
          * a blind correction factor... */
         dpi = dpi * 0.83f;
#endif

         /* Note: If we are running in windowed mode, this
          * 'display size' is actually the window size - which
          * kinda makes a mess of everything. Since we cannot
          * get fullscreen resolution when running in windowed
          * mode, there is nothing we can do about this. So just
          * treat the window as a display, and hope for the best... */
         display_size = diagonal_pixels / dpi;
         dpi_scale    = dpi / REFERENCE_DPI;

         /* Note: We have tried leveraging every possible metric
          * (and numerous studies on TV/monitor/mobile device
          * usage habits) to determine an appropriate auto scaling
          * factor. *None of these 'smart'/technical methods work
          * consistently in the real world* - there is simply too
          * much variance.
          * So instead we have implemented a very fuzzy/loose
          * method which is crude as can be, but actually has
          * some semblance of usability... */

         if (display_size > 24.0f)
         {
            /* DPI scaling fails miserably when using large
             * displays. Having a UI element that's 1 inch high
             * on all screens might seem like a good idea - until
             * you realise that a HTPC user is probably sitting
             * several metres from their TV, which makes something
             * 1 inch high virtually invisible.
             * So we make some assumptions:
             * - Normal size displays <= 24 inches are probably
             *   PC monitors, with an eye-to-screen distance of
             *   1 arm length. Under these conditions, fixed size
             *   (DPI scaled) UI elements should be visible for most
             *   users
             * - Large displays > 24 inches start to encroach on
             *   TV territory. Once we start working with TVs, we
             *   have to consider users sitting on a couch - and
             *   in this situation, we fall back to the age-old
             *   standard of UI elements occupying a fixed fraction
             *   of the display size (i.e. just look at the menu of
             *   any console system for the past decade)
             * - 24 -> 32 inches is a grey area, where the display
             *   might be a monitor or a TV. Above 32 inches, a TV
             *   is almost a certainty. So we simply lerp between
             *   dpi scaling and pixel scaling as the display size
             *   increases from 24 to 32 */
            float fraction = (display_size > 32.0f) ? 32.0f : display_size;
            fraction       = fraction - 24.0f;
            fraction       = fraction / (32.0f - 24.0f);

            scale = ((1.0f - fraction) * dpi_scale) + (fraction * pixel_scale);
         }
         else if (display_size < 12.0f)
         {
            /* DPI scaling also fails when using very small
             * displays - i.e. mobile devices (tablets/phones).
             * That 1 inch UI element is going to look pretty
             * dumb on a 5 inch screen in landscape orientation...
             * We're essentially in the opposite situation to the
             * TV case above, and it turns out that a similar
             * solution provides relief: as screen size reduces
             * from 12 inches to zero, we lerp from dpi scaling
             * to pixel scaling */
            float fraction = display_size / 12.0f;

            scale = ((1.0f - fraction) * pixel_scale) + (fraction * dpi_scale);
         }
         else
            scale = dpi_scale;
      }
      /* If DPI retrieval is unsupported, all we can do
       * is use the raw pixel scale */
      else
         scale = pixel_scale;

      scale_cached = true;
      last_width   = width;
      last_height  = height;
   }

   /* Apply user scaling factor */
   if (settings)
      return scale * ((settings->floats.menu_scale_factor > 0.0001f) ?
            settings->floats.menu_scale_factor : 1.0f);

   return scale;
}