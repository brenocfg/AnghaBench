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
struct bps_data {int /*<<< orphan*/  target_checksum; int /*<<< orphan*/  output_offset; int /*<<< orphan*/ * target_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bps_write(struct bps_data *bps, uint8_t data)
{
   bps->target_data[bps->output_offset++] = data;
   bps->target_checksum = ~(encoding_crc32(~bps->target_checksum, &data, 1));
}