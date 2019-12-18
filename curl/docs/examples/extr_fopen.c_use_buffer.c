#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t buffer_pos; int /*<<< orphan*/ * buffer; scalar_t__ buffer_len; } ;
typedef  TYPE_1__ URL_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int use_buffer(URL_FILE *file, size_t want)
{
  /* sort out buffer */
  if(file->buffer_pos <= want) {
    /* ditch buffer - write will recreate */
    free(file->buffer);
    file->buffer = NULL;
    file->buffer_pos = 0;
    file->buffer_len = 0;
  }
  else {
    /* move rest down make it available for later */
    memmove(file->buffer,
            &file->buffer[want],
            (file->buffer_pos - want));

    file->buffer_pos -= want;
  }
  return 0;
}