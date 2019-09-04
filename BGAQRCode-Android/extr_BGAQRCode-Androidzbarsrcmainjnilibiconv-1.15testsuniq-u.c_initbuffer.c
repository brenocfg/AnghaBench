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
struct linebuffer {int size; char* buffer; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
initbuffer (struct linebuffer *linebuffer)
{
  linebuffer->length = 0;
  linebuffer->size = 200;
  linebuffer->buffer = (char *) xmalloc (linebuffer->size);
}