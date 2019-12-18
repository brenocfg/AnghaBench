#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Corrupted; unsigned char* Message_Block; int Message_Block_Index; int Length_Low; int Length_High; scalar_t__ Computed; } ;
typedef  TYPE_1__ SHA1Context ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1ProcessMessageBlock (TYPE_1__*) ; 

void SHA1Input(     SHA1Context         *context,
                    const unsigned char *message_array,
                    unsigned            length)
{
   if (!length)
      return;

   if (context->Computed || context->Corrupted)
   {
      context->Corrupted = 1;
      return;
   }

   while(length-- && !context->Corrupted)
   {
      context->Message_Block[context->Message_Block_Index++] =
         (*message_array & 0xFF);

      context->Length_Low += 8;
      /* Force it to 32 bits */
      context->Length_Low &= 0xFFFFFFFF;
      if (context->Length_Low == 0)
      {
         context->Length_High++;
         /* Force it to 32 bits */
         context->Length_High &= 0xFFFFFFFF;
         if (context->Length_High == 0)
         {
            /* Message is too long */
            context->Corrupted = 1;
         }
      }

      if (context->Message_Block_Index == 64)
         SHA1ProcessMessageBlock(context);

      message_array++;
   }
}