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
typedef  int /*<<< orphan*/ * qr_point ;

/* Variables and functions */
 int /*<<< orphan*/  SVG_ABS ; 
 int /*<<< orphan*/  svg_path_end () ; 
 int /*<<< orphan*/  svg_path_moveto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_path_start (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qr_svg_points(const char *cls,
                                 qr_point *p,
                                 int n)
{
    int i;
    svg_path_start(cls, 1, 0, 0);
    for(i = 0; i < n; i++, p++)
        svg_path_moveto(SVG_ABS, p[0][0], p[0][1]);
    svg_path_end();
}