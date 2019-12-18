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
typedef  int uLong ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int Byte ;

/* Variables and functions */
 int EOF ; 
 int adler32 (int,int*,int) ; 
 int crc32 (int,int*,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char const*) ; 
 int /*<<< orphan*/  u16 (int) ; 
 int /*<<< orphan*/  u32 (int) ; 

__attribute__((used)) static int
read_one_file(FILE *ip, const char *name)
{
   uLong length = 0;
   uLong a32 = adler32(0, NULL, 0);
   uLong c32 = crc32(0, NULL, 0);
   Byte header[132];

   for (;;)
   {
      int ch = getc(ip);
      Byte b;

      if (ch == EOF) break;

      b = (Byte)ch;

      if (length < sizeof header)
         header[length] = b;

      ++length;
      a32 = adler32(a32, &b, 1);
      c32 = crc32(c32, &b, 1);
   }

   if (ferror(ip))
      return 0;

   /* Success */
   printf("PNG_ICC_CHECKSUM(0x%8.8lx, 0x%8.8lx,\n   PNG_MD5("
      "0x%2.2x%2.2x%2.2x%2.2x, 0x%2.2x%2.2x%2.2x%2.2x, 0x%2.2x%2.2x%2.2x%2.2x,"
      " 0x%2.2x%2.2x%2.2x%2.2x), %d,\n"
      "   \"%4.4d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d\", %lu, \"%s\")\n",
      (unsigned long)a32, (unsigned long)c32,
      header[84], header[85], header[86], header[87],
      header[88], header[89], header[90], header[91],
      header[92], header[93], header[94], header[95],
      header[96], header[97], header[98], header[99],
#     define u16(x) (header[x] * 256 + header[x+1])
#     define u32(x) (u16(x) * 65536 + u16(x+2))
      u32(64), u16(24), u16(26), u16(28), u16(30), u16(32), u16(34),
      (unsigned long)length, name);

   return 1;
}