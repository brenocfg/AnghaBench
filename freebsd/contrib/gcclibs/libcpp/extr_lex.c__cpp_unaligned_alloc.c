#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* u_buff; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_7__ {unsigned char* cur; unsigned char* limit; struct TYPE_7__* next; } ;
typedef  TYPE_2__ _cpp_buff ;

/* Variables and functions */
 TYPE_2__* _cpp_get_buff (TYPE_1__*,size_t) ; 

unsigned char *
_cpp_unaligned_alloc (cpp_reader *pfile, size_t len)
{
  _cpp_buff *buff = pfile->u_buff;
  unsigned char *result = buff->cur;

  if (len > (size_t) (buff->limit - result))
    {
      buff = _cpp_get_buff (pfile, len);
      buff->next = pfile->u_buff;
      pfile->u_buff = buff;
      result = buff->cur;
    }

  buff->cur = result + len;
  return result;
}