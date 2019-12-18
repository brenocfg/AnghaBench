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
typedef  int /*<<< orphan*/  chdstream_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ chdstream_read (int /*<<< orphan*/ *,char*,int) ; 

int chdstream_getc(chdstream_t *stream)
{
   char c = 0;

   if (chdstream_read(stream, &c, sizeof(c) != sizeof(c)))
      return EOF;

   return c;
}