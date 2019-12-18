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
typedef  enum TiffType { ____Placeholder_TiffType } TiffType ;
struct TYPE_3__ {int tiff_type; } ;
typedef  TYPE_1__ TiffContext ;

/* Variables and functions */

__attribute__((used)) static void tiff_set_type(TiffContext *s, enum TiffType tiff_type) {
    if (s->tiff_type < tiff_type) // Prioritize higher-valued entries
        s->tiff_type = tiff_type;
}