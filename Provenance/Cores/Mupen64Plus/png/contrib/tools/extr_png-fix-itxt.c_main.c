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
typedef  int uInt ;
typedef  scalar_t__ length ;
typedef  unsigned char crc ;

/* Variables and functions */
 int /*<<< orphan*/  GETBREAK ; 
 int MAX_LENGTH ; 
 unsigned char* Z_NULL ; 
 unsigned long crc32 (unsigned long,unsigned char*,int) ; 
 int /*<<< orphan*/  putchar (unsigned char) ; 

int
main(void)
{
   unsigned int i;
   unsigned char buf[MAX_LENGTH];
   unsigned long crc;
   unsigned char c;
   int inchar;

/* Skip 8-byte signature */
   for (i=8; i; i--)
   {
      GETBREAK;
      putchar(c);
   }

if (inchar == c) /* !EOF */
for (;;)
 {
   /* Read the length */
   unsigned long length; /* must be 32 bits! */
   GETBREAK; buf[0] = c; length  = c; length <<= 8;
   GETBREAK; buf[1] = c; length += c; length <<= 8;
   GETBREAK; buf[2] = c; length += c; length <<= 8;
   GETBREAK; buf[3] = c; length += c;

   /* Read the chunkname */
   GETBREAK; buf[4] = c;
   GETBREAK; buf[5] = c;
   GETBREAK; buf[6] = c;
   GETBREAK; buf[7] = c;


   /* The iTXt chunk type expressed as integers is (105, 84, 88, 116) */
   if (buf[4] == 105 && buf[5] == 84 && buf[6] == 88 && buf[7] == 116)
   {
      if (length >= MAX_LENGTH-12)
         break;  /* To do: handle this more gracefully */

      /* Initialize the CRC */
      crc = crc32(0, Z_NULL, 0);

      /* Copy the data bytes */
      for (i=8; i < length + 12; i++)
      {
         GETBREAK; buf[i] = c;
      }

      if (inchar != c) /* EOF */
         break;

      /* Calculate the CRC */
      crc = crc32(crc, buf+4, (uInt)length+4);

      for (;;)
      {
        /* Check the CRC */
        if (((crc >> 24) & 0xffU) == buf[length+8] &&
            ((crc >> 16) & 0xffU) == buf[length+9] &&
            ((crc >>  8) & 0xffU) == buf[length+10] &&
            ((crc      ) & 0xffU) == buf[length+11])
           break;

        length++;

        if (length >= MAX_LENGTH-12)
           break;

        GETBREAK;
        buf[length+11] = c;

        /* Update the CRC */
        crc = crc32(crc, buf+7+length, 1);
      }

      if (inchar != c) /* EOF */
         break;

      /* Update length bytes */
      buf[0] = (unsigned char)((length >> 24) & 0xffU);
      buf[1] = (unsigned char)((length >> 16) & 0xffU);
      buf[2] = (unsigned char)((length >>  8) & 0xffU);
      buf[3] = (unsigned char)((length      ) & 0xffU);

      /* Write the fixed iTXt chunk (length, name, data, crc) */
      for (i=0; i<length+12; i++)
         putchar(buf[i]);
   }

   else
   {
      if (inchar != c) /* EOF */
         break;

      /* Copy bytes that were already read (length and chunk name) */
      for (i=0; i<8; i++)
         putchar(buf[i]);

      /* Copy data bytes and CRC */
      for (i=8; i< length+12; i++)
      {
         GETBREAK;
         putchar(c);
      }

      if (inchar != c) /* EOF */
      {
         break;
      }

   /* The IEND chunk type expressed as integers is (73, 69, 78, 68) */
      if (buf[4] == 73 && buf[5] == 69 && buf[6] == 78 && buf[7] == 68)
         break;
   }

   if (inchar != c) /* EOF */
      break;

   if (buf[4] == 73 && buf[5] == 69 && buf[6] == 78 && buf[7] == 68)
     break;
 }

 return 0;
}