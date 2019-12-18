#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mi_valid; int /*<<< orphan*/ * mi_cmacro; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_6__ {int buffer_valid; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * cmacro; } ;
typedef  TYPE_2__ _cpp_file ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

void
_cpp_pop_file_buffer (cpp_reader *pfile, _cpp_file *file)
{
  /* Record the inclusion-preventing macro, which could be NULL
     meaning no controlling macro.  */
  if (pfile->mi_valid && file->cmacro == NULL)
    file->cmacro = pfile->mi_cmacro;

  /* Invalidate control macros in the #including file.  */
  pfile->mi_valid = false;

  if (file->buffer)
    {
      free ((void *) file->buffer);
      file->buffer = NULL;
      file->buffer_valid = false;
    }
}