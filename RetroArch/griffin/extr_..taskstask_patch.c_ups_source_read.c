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
struct ups_data {scalar_t__ source_offset; scalar_t__ source_length; int* source_data; int /*<<< orphan*/  source_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static uint8_t ups_source_read(struct ups_data *data)
{
   if (data && data->source_offset < data->source_length)
   {
      uint8_t n = data->source_data[data->source_offset++];
      data->source_checksum =
         ~(encoding_crc32(~data->source_checksum, &n, 1));
      return n;
   }
   return 0x00;
}