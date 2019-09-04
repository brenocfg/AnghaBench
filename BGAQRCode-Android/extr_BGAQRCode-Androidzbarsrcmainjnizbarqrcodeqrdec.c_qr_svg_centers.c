#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nedge_pts; TYPE_1__* edge_pts; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_2__ qr_finder_center ;
struct TYPE_4__ {int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVG_ABS ; 
 int /*<<< orphan*/  svg_path_end () ; 
 int /*<<< orphan*/  svg_path_moveto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_path_start (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qr_svg_centers (const qr_finder_center *centers,
                                   int ncenters)
{
    int i, j;
    svg_path_start("centers", 1, 0, 0);
    for(i = 0; i < ncenters; i++)
        svg_path_moveto(SVG_ABS, centers[i].pos[0], centers[i].pos[1]);
    svg_path_end();

    svg_path_start("edge-pts", 1, 0, 0);
    for(i = 0; i < ncenters; i++) {
        const qr_finder_center *cen = centers + i;
        for(j = 0; j < cen->nedge_pts; j++)
            svg_path_moveto(SVG_ABS,
                            cen->edge_pts[j].pos[0], cen->edge_pts[j].pos[1]);
    }
    svg_path_end();
}