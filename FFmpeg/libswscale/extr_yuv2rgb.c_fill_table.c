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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;

/* Variables and functions */
 int YUVRGB_TABLE_HEADROOM ; 
 int const av_clip_uint8 (int) ; 

__attribute__((used)) static void fill_table(uint8_t* table[256 + 2*YUVRGB_TABLE_HEADROOM], const int elemsize,
                       const int64_t inc, void *y_tab)
{
    int i;
    uint8_t *y_table = y_tab;

    y_table -= elemsize * (inc >> 9);

    for (i = 0; i < 256 + 2*YUVRGB_TABLE_HEADROOM; i++) {
        int64_t cb = av_clip_uint8(i-YUVRGB_TABLE_HEADROOM)*inc;
        table[i] = y_table + elemsize * (cb >> 16);
    }
}