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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;

/* Variables and functions */

__attribute__((used)) static void avi_track_from_chunk_id(VC_CONTAINER_FOURCC_T chunk_id, uint16_t *data_type, uint16_t *track_num)
{
   *track_num = (((uint8_t*)&chunk_id)[0] - 48) * 10 + ((uint8_t*)&chunk_id)[1] - 48;
   *data_type = (uint32_t)chunk_id >> 16;
}