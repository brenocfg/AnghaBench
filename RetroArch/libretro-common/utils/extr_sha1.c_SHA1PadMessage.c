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
struct TYPE_4__ {int Message_Block_Index; int* Message_Block; int Length_High; int Length_Low; } ;
typedef  TYPE_1__ SHA1Context ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1ProcessMessageBlock (TYPE_1__*) ; 

void SHA1PadMessage(SHA1Context *context)
{
   /*
    *  Check to see if the current message block is too small to hold
    *  the initial padding bits and length.  If so, we will pad the
    *  block, process it, and then continue padding into a second
    *  block.
    */
   if (context->Message_Block_Index > 55)
   {
      context->Message_Block[context->Message_Block_Index++] = 0x80;
      while(context->Message_Block_Index < 64)
         context->Message_Block[context->Message_Block_Index++] = 0;

      SHA1ProcessMessageBlock(context);

      while(context->Message_Block_Index < 56)
         context->Message_Block[context->Message_Block_Index++] = 0;
   }
   else
   {
      context->Message_Block[context->Message_Block_Index++] = 0x80;
      while(context->Message_Block_Index < 56)
         context->Message_Block[context->Message_Block_Index++] = 0;
   }

   /*
    *  Store the message length as the last 8 octets
    */
   context->Message_Block[56] = (context->Length_High >> 24) & 0xFF;
   context->Message_Block[57] = (context->Length_High >> 16) & 0xFF;
   context->Message_Block[58] = (context->Length_High >> 8) & 0xFF;
   context->Message_Block[59] = (context->Length_High) & 0xFF;
   context->Message_Block[60] = (context->Length_Low >> 24) & 0xFF;
   context->Message_Block[61] = (context->Length_Low >> 16) & 0xFF;
   context->Message_Block[62] = (context->Length_Low >> 8) & 0xFF;
   context->Message_Block[63] = (context->Length_Low) & 0xFF;

   SHA1ProcessMessageBlock(context);
}