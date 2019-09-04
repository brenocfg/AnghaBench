#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ Window ;
struct TYPE_2__ {scalar_t__ RootWindow; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  XA_WINDOW ; 
 int /*<<< orphan*/  XFree (scalar_t__*) ; 
 TYPE_1__ fgDisplay ; 
 int /*<<< orphan*/  fghGetAtom (char*) ; 
 int fghGetWindowProperty (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  free (scalar_t__**) ; 
 scalar_t__** malloc (int) ; 

__attribute__((used)) static int fghNetWMSupported(void)
{
  Atom wm_check;
  Window ** window_ptr_1;

  int number_of_windows;
  int net_wm_supported;


  net_wm_supported = 0;

  wm_check = fghGetAtom("_NET_SUPPORTING_WM_CHECK");
  window_ptr_1 = malloc(sizeof(Window *));

  /*
   * Check that the window manager has set this property on the root window.
   * The property must be the ID of a child window.
   */
  number_of_windows = fghGetWindowProperty(fgDisplay.RootWindow,
                                           wm_check,
                                           XA_WINDOW,
                                           (unsigned char **) window_ptr_1);
  if (number_of_windows == 1)
    {
      Window ** window_ptr_2;

      window_ptr_2 = malloc(sizeof(Window *));

      /* Check that the window has the same property set to the same value. */
      number_of_windows = fghGetWindowProperty(**window_ptr_1,
                                               wm_check,
                                               XA_WINDOW,
                                               (unsigned char **) window_ptr_2);
      if ((number_of_windows == 1) && (**window_ptr_1 == **window_ptr_2))
      {
        /* NET WM compliant */
        net_wm_supported = 1;
      }

      XFree(*window_ptr_2);
      free(window_ptr_2);
    }

        XFree(*window_ptr_1);
        free(window_ptr_1);

        return net_wm_supported;
}