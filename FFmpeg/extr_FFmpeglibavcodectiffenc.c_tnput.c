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
typedef  enum TiffTypes { ____Placeholder_TiffTypes } TiffTypes ;

/* Variables and functions */
 int* type_sizes2 ; 

__attribute__((used)) static void tnput(uint8_t **p, int n, const uint8_t *val, enum TiffTypes type,
                  int flip)
{
    int i;
#if HAVE_BIGENDIAN
    flip ^= ((int[]) { 0, 0, 0, 1, 3, 3 })[type];
#endif
    for (i = 0; i < n * type_sizes2[type]; i++)
        *(*p)++ = val[i ^ flip];
}