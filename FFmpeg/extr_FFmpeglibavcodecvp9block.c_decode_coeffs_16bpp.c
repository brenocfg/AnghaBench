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
typedef  int /*<<< orphan*/  VP9TileData ;

/* Variables and functions */
 int decode_coeffs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_coeffs_16bpp(VP9TileData *td)
{
    return decode_coeffs(td, 0);
}