#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sup_encodings ;
struct TYPE_8__ {int size; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__* encodings; TYPE_4__ header; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ MMAL_SUPPORTED_ENCODINGS_T ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;

/* Variables and functions */
 int MAX_ENCODINGS_NUM ; 
 scalar_t__ MMAL_ENCODING_BGR24 ; 
 scalar_t__ MMAL_ENCODING_RGB24 ; 
 scalar_t__ MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_PARAMETER_SUPPORTED_ENCODINGS ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ *,TYPE_4__*) ; 

int mmal_util_rgb_order_fixed(MMAL_PORT_T *port)
{
   int new_fw = 0;
   MMAL_STATUS_T ret;
   //Firmware support of RGB24 vs BGR24 colour ordering from camera
   //and video splitter components has been corrected as of June 2016.
   //New firmwares always report MMAL_ENCODING_RGB24 before BGR24, and
   //that is the format we want.
   //Old firmware reported BGR24 first, and also returned an error on
   //the still port on querying MMAL_PARAMETER_SUPPORTED_ENCODINGS.

   MMAL_SUPPORTED_ENCODINGS_T sup_encodings = {{MMAL_PARAMETER_SUPPORTED_ENCODINGS, sizeof(sup_encodings)}, {0}};
   ret = mmal_port_parameter_get(port, &sup_encodings.header);
   if (ret == MMAL_SUCCESS || ret == MMAL_ENOSPC)
   {
      //Allow ENOSPC error and hope that the desired formats are in the first
      //MAX_ENCODINGS_NUM entries.
      int i;
      int num_encodings = (sup_encodings.header.size - sizeof(sup_encodings.header)) /
          sizeof(sup_encodings.encodings[0]);
      if(num_encodings > MAX_ENCODINGS_NUM)
         num_encodings = MAX_ENCODINGS_NUM;
      for (i=0; i<num_encodings; i++)
      {
         if (sup_encodings.encodings[i] == MMAL_ENCODING_BGR24)
         {
            //Found BGR24 first - old firmware.
            break;
         }
         if (sup_encodings.encodings[i] == MMAL_ENCODING_RGB24)
         {
            //Found RGB24 first - new firmware, so use RGB24.
            new_fw = 1;
         }
      }
   }
   return new_fw;
}