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
struct TYPE_4__ {scalar_t__ chd; struct TYPE_4__* hunkmem; } ;
typedef  TYPE_1__ chdstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  chd_close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void chdstream_close(chdstream_t *stream)
{
   if (stream)
   {
      if (stream->hunkmem)
         free(stream->hunkmem);
      if (stream->chd)
         chd_close(stream->chd);
      free(stream);
   }
}