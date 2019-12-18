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

/* Variables and functions */
 unsigned char inp (int) ; 
 unsigned char* normal_keys ; 
 int /*<<< orphan*/  outp (int,int) ; 

__attribute__((used)) static void keyb_int(void)
{
   static unsigned char buffer = 0;
   unsigned char rawcode       = inp(0x60);
   /* read scancode from keyboard controller */
   unsigned char make_break    = !(rawcode & 0x80);
   /* bit 7: 0 = make, 1 = break */
   int scancode                = rawcode & 0x7F;

   if (buffer == 0xE0)
   {
      /* second byte of an extended key */
      if (scancode < 0x60)
         normal_keys[scancode | (1 << 8)] = make_break;

      buffer = 0;
   }
   else if (buffer >= 0xE1 && buffer <= 0xE2)
      buffer = 0; /* ignore these extended keys */
   else if (rawcode >= 0xE0 && rawcode <= 0xE2)
      buffer = rawcode; /* first byte of an extended key */
   else if (scancode < 0x60)
      normal_keys[scancode] = make_break;

   outp(0x20, 0x20); /* must send EOI to finish interrupt */
}