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
typedef  int HDMI_ASPECT_T ;

/* Variables and functions */
#define  HDMI_ASPECT_14_9 134 
#define  HDMI_ASPECT_15_9 133 
#define  HDMI_ASPECT_16_10 132 
#define  HDMI_ASPECT_16_9 131 
#define  HDMI_ASPECT_4_3 130 
#define  HDMI_ASPECT_5_4 129 
#define  HDMI_ASPECT_64_27 128 

__attribute__((used)) static const char *aspect_ratio_str(HDMI_ASPECT_T aspect_ratio) {
   switch(aspect_ratio) {
   case HDMI_ASPECT_4_3:
      return "4:3";
   case HDMI_ASPECT_14_9:
      return "14:9";
   case HDMI_ASPECT_16_9:
      return "16:9";
   case HDMI_ASPECT_5_4:
      return "5:4";
   case HDMI_ASPECT_16_10:
      return "16:10";
   case HDMI_ASPECT_15_9:
      return "15:9";
   case HDMI_ASPECT_64_27:
      return "64:27 (21:9)";
   default:
      return "unknown AR";
   }
}