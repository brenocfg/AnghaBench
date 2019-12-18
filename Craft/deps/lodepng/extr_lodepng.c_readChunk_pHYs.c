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
struct TYPE_3__ {int phys_defined; int phys_x; int phys_y; unsigned char phys_unit; } ;
typedef  TYPE_1__ LodePNGInfo ;

/* Variables and functions */

__attribute__((used)) static unsigned readChunk_pHYs(LodePNGInfo* info, const unsigned char* data, size_t chunkLength)
{
  if(chunkLength != 9) return 74; /*invalid pHYs chunk size*/

  info->phys_defined = 1;
  info->phys_x = 16777216 * data[0] + 65536 * data[1] + 256 * data[2] + data[3];
  info->phys_y = 16777216 * data[4] + 65536 * data[5] + 256 * data[6] + data[7];
  info->phys_unit = data[8];

  return 0; /* OK */
}