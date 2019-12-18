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
struct TYPE_3__ {int faceStyleFlags; int textColorRGBA; } ;
typedef  TYPE_1__ StyleRecord ;

/* Variables and functions */
 int BOLD ; 
 int HB_RGB_TO_BGR (int) ; 
 int ITALIC ; 
 int UNDERLINE ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int write_ssa_markup(char *dst, StyleRecord *style)
{
    if (style == NULL)
    {
        sprintf(dst, "{\\r}");
        return strlen(dst);
    }
    sprintf(dst, "{\\i%d\\b%d\\u%d\\1c&H%X&\\1a&H%02X&}",
        !!(style->faceStyleFlags & ITALIC),
        !!(style->faceStyleFlags & BOLD),
        !!(style->faceStyleFlags & UNDERLINE),
        HB_RGB_TO_BGR(style->textColorRGBA >> 8),
        255 - (style->textColorRGBA & 0xFF)); // SSA alpha is inverted 0==opaque

    return strlen(dst);
}