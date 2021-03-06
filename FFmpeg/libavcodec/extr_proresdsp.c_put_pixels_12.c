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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_pixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void put_pixels_12(uint16_t *dst, ptrdiff_t linesize, const int16_t *in)
{
    put_pixel(dst, linesize, in, 12);
}