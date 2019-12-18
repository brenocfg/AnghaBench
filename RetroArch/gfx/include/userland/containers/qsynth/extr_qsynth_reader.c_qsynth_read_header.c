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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  BI16 (char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T qsynth_read_header(uint8_t *data, uint32_t *tracks,
   uint32_t *division, uint8_t *fps, uint8_t *dpf)
{
   if(data[0] != 'M' || data[1] != 'T' || data[2] != 'h' || data[3] != 'd' ||
      data[4] != 0   || data[5] != 0   || data[6] != 0   || data[7] != 6)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   if(data[12] < 0x80)
   {
      if(division) *division = BI16(data+12);
   }
   else
   {
      if(fps) *fps = 256-data[12];
      if(dpf) *dpf = data[13];
   }

   if(tracks) *tracks = BI16(data+10);

   return VC_CONTAINER_SUCCESS;
}