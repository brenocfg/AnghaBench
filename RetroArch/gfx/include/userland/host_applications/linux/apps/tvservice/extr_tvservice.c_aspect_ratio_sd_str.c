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
typedef  int SDTV_ASPECT_T ;

/* Variables and functions */
#define  SDTV_ASPECT_14_9 130 
#define  SDTV_ASPECT_16_9 129 
#define  SDTV_ASPECT_4_3 128 

__attribute__((used)) static const char *aspect_ratio_sd_str(SDTV_ASPECT_T aspect_ratio) {
   switch(aspect_ratio) {
   case SDTV_ASPECT_4_3:
      return "4:3";
   case SDTV_ASPECT_14_9:
      return "14:9";
   case SDTV_ASPECT_16_9:
      return "16:9";
   default:
      return "unknown AR";
   }
}