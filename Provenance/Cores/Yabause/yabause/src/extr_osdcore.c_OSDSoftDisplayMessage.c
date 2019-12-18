#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pixel_t ;
struct TYPE_3__ {int type; char* message; } ;
typedef  TYPE_1__ OSDMessage_struct ;

/* Variables and functions */
#define  OSDMSG_STATUS 128 
 int /*<<< orphan*/  TitanWriteColor (int /*<<< orphan*/ *,int,int,int,int) ; 
 char** font ; 

void OSDSoftDisplayMessage(OSDMessage_struct * message, pixel_t * buffer, int w, int h)
{
   int i;
   char * c;
   int loffset = 0;

   if (buffer == NULL) return;

   switch (message->type)
   {
      case OSDMSG_STATUS:
         loffset = h - 48;
         break;
   }

   c = message->message;
   i = 0;
   while(*c)
   {
      if (*c >= 47)
      {
         int first_line, l, p;
         first_line = *c * 10;
         for(l = 0;l < 10;l++)
         {
            for(p = 0;p < 9;p++)
            {
               if (font[first_line + l][p] == '.')
                  TitanWriteColor(buffer, w, (i * 8) + 20 + p, loffset + l + 20, 0xFF000000);
               else if (font[first_line + l][p] == '#')
                  TitanWriteColor(buffer, w, (i * 8) + 20 + p, loffset + l + 20, 0xFFFFFFFF);
            }
         }
      }
      c++;
      i++;
   }
}