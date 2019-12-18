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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_STD (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int vc_tv_hdmi_ddc_read (size_t,int,int*) ; 

__attribute__((used)) static int dump_edid( const char *filename )
{
   uint8_t buffer[128];
   size_t written = 0, offset = 0;
   int i, extensions = 0;
   FILE *fp = NULL;
   int siz = vc_tv_hdmi_ddc_read(offset, sizeof (buffer), buffer);
   offset += sizeof( buffer);
   /* First block always exist */
   if (siz == sizeof(buffer) && (fp = fopen(filename, "wb")) != NULL) {
      written += fwrite(buffer, 1, sizeof buffer, fp);
      extensions = buffer[0x7e]; /* This tells you how many more blocks to read */
      for(i = 0; i < extensions; i++, offset += sizeof( buffer)) {
         siz = vc_tv_hdmi_ddc_read(offset, sizeof( buffer), buffer);
         if(siz == sizeof(buffer)) {
            written += fwrite(buffer, 1, sizeof (buffer), fp);
         } else {
            break;
         }
      }
   }
   if (fp)
      fclose(fp);
   if(written) {
      LOG_STD( "Written %d bytes to %s", written, filename);
   } else {
      LOG_STD( "Nothing written!");
   }
   return written < sizeof(buffer);
}