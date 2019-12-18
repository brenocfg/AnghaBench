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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline void avpriv_codec2_make_extradata(uint8_t *ptr, int mode) {
    //version 0.8 as of 2017-12-23 (r3386)
    ptr[0] = 0;     //major
    ptr[1] = 8;     //minor
    ptr[2] = mode;  //mode
    ptr[3] = 0;     //flags
}