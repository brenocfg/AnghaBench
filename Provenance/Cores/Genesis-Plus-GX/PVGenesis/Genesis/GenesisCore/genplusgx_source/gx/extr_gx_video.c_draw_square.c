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

/* Variables and functions */
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 int /*<<< orphan*/  draw_vert (int,double,double) ; 

__attribute__((used)) static inline void draw_square(void)
{
  GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
  draw_vert(3, 0.0, 0.0);
  draw_vert(2, 1.0, 0.0);
  draw_vert(1, 1.0, 1.0);
  draw_vert(0, 0.0, 1.0);
  GX_End();
}