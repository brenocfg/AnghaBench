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
struct ups_data {size_t target_offset; size_t target_length; int /*<<< orphan*/  target_checksum; int /*<<< orphan*/ * target_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ups_target_write(struct ups_data *data, uint8_t n)
{

   if (data && data->target_offset < data->target_length)
   {
      data->target_data[data->target_offset] = n;
      data->target_checksum =
         ~(encoding_crc32(~data->target_checksum, &n, 1));
   }

   if (data)
      data->target_offset++;
}