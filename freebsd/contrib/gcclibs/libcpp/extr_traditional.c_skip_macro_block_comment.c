#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
struct TYPE_5__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_4__ {char* cur; } ;

/* Variables and functions */

__attribute__((used)) static void
skip_macro_block_comment (cpp_reader *pfile)
{
  const uchar *cur = pfile->buffer->cur;

  cur++;
  if (*cur == '/')
    cur++;

  /* People like decorating comments with '*', so check for '/'
     instead for efficiency.  */
  while(! (*cur++ == '/' && cur[-2] == '*') )
    ;

  pfile->buffer->cur = cur;
}