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
#define  STREAMING_MODE_CUSTOM 131 
#define  STREAMING_MODE_LOCAL 130 
#define  STREAMING_MODE_TWITCH 129 
#define  STREAMING_MODE_YOUTUBE 128 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_streaming_mode(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   /* TODO/FIXME - localize this */
   switch (*setting->value.target.unsigned_integer)
   {
      case STREAMING_MODE_TWITCH:
         strlcpy(s, "Twitch", len);
         break;
      case STREAMING_MODE_YOUTUBE:
         strlcpy(s, "YouTube", len);
         break;
      case STREAMING_MODE_LOCAL:
         strlcpy(s, "Local", len);
         break;
      case STREAMING_MODE_CUSTOM:
         strlcpy(s, "Custom", len);
         break;
   }
}