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
struct TYPE_3__ {int key_defined; unsigned int key_r; unsigned int key_g; unsigned int key_b; } ;
typedef  TYPE_1__ LodePNGColorMode ;

/* Variables and functions */

__attribute__((used)) static void setColorKeyFrom16bit(LodePNGColorMode* mode_out, unsigned r, unsigned g, unsigned b, unsigned bitdepth)
{
  unsigned mask = (1 << bitdepth) - 1;
  mode_out->key_defined = 1;
  mode_out->key_r = r & mask;
  mode_out->key_g = g & mask;
  mode_out->key_b = b & mask;
}