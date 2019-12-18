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
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int EOF ; 
 int filestream_read (int /*<<< orphan*/ *,char*,int) ; 

int filestream_getc(RFILE *stream)
{
   char c = 0;
   if (!stream)
      return EOF;
   if (filestream_read(stream, &c, 1) == 1)
      return (int)(unsigned char)c;
   return EOF;
}