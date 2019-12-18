#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  deviceSupportsGamma; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 scalar_t__ GAMMA_MINMAJOR ; 
 scalar_t__ GAMMA_MINMINOR ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  XF86VidModeGetGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpy ; 
 TYPE_2__ glConfig ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  scrnum ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vidmode_InitialGamma ; 
 scalar_t__ vidmode_MajorVersion ; 
 scalar_t__ vidmode_MinorVersion ; 
 scalar_t__ vidmode_ext ; 

__attribute__((used)) static void GLW_InitGamma()
{
  /* Minimum extension version required */
  #define GAMMA_MINMAJOR 2
  #define GAMMA_MINMINOR 0
  
  glConfig.deviceSupportsGamma = qfalse;

  if (vidmode_ext)
  {
    if (vidmode_MajorVersion < GAMMA_MINMAJOR || 
        (vidmode_MajorVersion == GAMMA_MINMAJOR && vidmode_MinorVersion < GAMMA_MINMINOR)) {
      ri.Printf( PRINT_ALL, "XF86 Gamma extension not supported in this version\n");
      return;
    }
    XF86VidModeGetGamma(dpy, scrnum, &vidmode_InitialGamma);
    ri.Printf( PRINT_ALL, "XF86 Gamma extension initialized\n");
    glConfig.deviceSupportsGamma = qtrue;
  }
}