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
typedef  void uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

__attribute__((used)) static inline void linecpy(void *dest, const void *src, int lines, int stride) {
    if (stride > 0) {
        memcpy(dest, src, lines*stride);
    } else {
        memcpy((uint8_t*)dest+(lines-1)*stride, (const uint8_t*)src+(lines-1)*stride, -lines*stride);
    }
}