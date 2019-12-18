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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int encoding_crc32 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int main(int argc, const char* argv[])
{
   if (argc != 2 )
   {
      fprintf( stderr, "Usage: crc32 <filename>\n" );
      return 1;
   }

   FILE *file = fopen(argv[1], "rb");

   if (file)
   {
      uint32_t crc = encoding_crc32(0L, NULL, 0 );

      for (;;)
      {
         uint8_t buffer[16384];

         int numread = fread((void*)buffer, 1, sizeof(buffer), file);

         if (numread > 0)
            crc = encoding_crc32( crc, buffer, numread );
         else
            break;
      }

      fclose(file);

      printf("%08x\n", crc);
      return 0;
   }

   fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
   return 1;
}