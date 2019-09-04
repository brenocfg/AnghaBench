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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  enum TiffTypes { ____Placeholder_TiffTypes } TiffTypes ;
typedef  enum TiffTags { ____Placeholder_TiffTags } TiffTags ;
typedef  int /*<<< orphan*/  TiffEncoderContext ;

/* Variables and functions */
 int TIFF_SHORT ; 
 int add_entry (int /*<<< orphan*/ *,int,int,int,void*) ; 

__attribute__((used)) static int add_entry1(TiffEncoderContext *s,
                      enum TiffTags tag, enum TiffTypes type, int val)
{
    uint16_t w  = val;
    uint32_t dw = val;
    return add_entry(s, tag, type, 1,
                     type == TIFF_SHORT ? (void *)&w : (void *)&dw);
}