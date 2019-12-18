#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GhbSurfaceHints ;
typedef  int /*<<< orphan*/  GhbSurface ;
typedef  int /*<<< orphan*/  GdkGeometry ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_window_set_geometry_hints (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ghb_surface_set_geometry_hints(GhbSurface * surface,
                               const GdkGeometry * geometry,
                               GhbSurfaceHints geom_mask)
{
    gdk_window_set_geometry_hints(surface, geometry, geom_mask);
}