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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int qsynth_read_variable (int*,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T qsynth_read_event(uint8_t *data, uint32_t *used, uint8_t *last,
                                               uint32_t *time, uint32_t *tempo, uint32_t *end)
{
   int read;

   // need at least 4 bytes here
   read = qsynth_read_variable(data, time);

   if(data[read] == 0xff) // meta event
   {
      uint32_t len;
      uint8_t type = data[read+1];

      read += 2;
      read += qsynth_read_variable(data+read, &len);

      if(type == 0x2f) // end of track
      {
         if(len != 0)
            return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

         *end = 1;
      }
      else if(type == 0x51) // tempo event
      {
         if(len != 3)
            return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

         *tempo = (data[read]<<16) | (data[read+1]<<8) | data[read+2];
      }

      read += len;
   }
   else if(data[read] == 0xf0 || data[read] == 0xf7) // sysex events
   {
      uint32_t len;
      read += 1;
      read += qsynth_read_variable(data+read, &len) + len;
   }
   else // midi event
   {
      uint8_t type;

      if(data[read] < 128)
         type = *last;
      else
      {
         type = data[read] >> 4;
         *last = type;
         read++;
      }

      switch(type) {
      case 8: case 9: case 0xa: case 0xb: case 0xe:
         read += 2;
         break;
      case 0xc: case 0xd:
         read += 1;
         break;
      default:
         return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
      }
   }

   *used = read;
   return VC_CONTAINER_SUCCESS;
}