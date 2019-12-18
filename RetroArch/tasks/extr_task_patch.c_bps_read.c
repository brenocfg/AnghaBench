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
struct bps_data {int /*<<< orphan*/  modify_checksum; int /*<<< orphan*/  modify_offset; int /*<<< orphan*/ * modify_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t bps_read(struct bps_data *bps)
{
   uint8_t data         = bps->modify_data[bps->modify_offset++];
   bps->modify_checksum = ~(encoding_crc32(
         ~bps->modify_checksum, &data, 1));
   return data;
}