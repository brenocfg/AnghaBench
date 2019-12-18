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
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int filestream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  form_bmp_header (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static bool write_header_bmp(RFILE *file, unsigned width, unsigned height, bool is32bpp)
{
   uint8_t header[54];
   form_bmp_header(header, width, height, is32bpp);
   return filestream_write(file, header, sizeof(header)) == sizeof(header);
}