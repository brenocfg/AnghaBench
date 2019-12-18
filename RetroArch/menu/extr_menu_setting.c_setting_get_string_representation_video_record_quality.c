#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
#define  RECORD_CONFIG_TYPE_RECORDING_APNG 136 
#define  RECORD_CONFIG_TYPE_RECORDING_CUSTOM 135 
#define  RECORD_CONFIG_TYPE_RECORDING_GIF 134 
#define  RECORD_CONFIG_TYPE_RECORDING_HIGH_QUALITY 133 
#define  RECORD_CONFIG_TYPE_RECORDING_LOSSLESS_QUALITY 132 
#define  RECORD_CONFIG_TYPE_RECORDING_LOW_QUALITY 131 
#define  RECORD_CONFIG_TYPE_RECORDING_MED_QUALITY 130 
#define  RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST 129 
#define  RECORD_CONFIG_TYPE_RECORDING_WEBM_HIGH_QUALITY 128 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_video_record_quality(rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   /* TODO/FIXME - localize this */
   switch (*setting->value.target.unsigned_integer)
   {
      case RECORD_CONFIG_TYPE_RECORDING_CUSTOM:
         strlcpy(s, "Custom", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_LOW_QUALITY:
         strlcpy(s, "Low", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_MED_QUALITY:
         strlcpy(s, "Medium", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_HIGH_QUALITY:
         strlcpy(s, "High", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_LOSSLESS_QUALITY:
         strlcpy(s, "Lossless", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST:
         strlcpy(s, "WebM Fast", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_WEBM_HIGH_QUALITY:
         strlcpy(s, "WebM High Quality", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_GIF:
         strlcpy(s, "GIF", len);
         break;
      case RECORD_CONFIG_TYPE_RECORDING_APNG:
         strlcpy(s, "APNG", len);
         break;
   }
}