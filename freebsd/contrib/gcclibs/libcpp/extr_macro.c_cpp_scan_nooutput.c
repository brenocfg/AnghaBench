#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  prevent_expansion; int /*<<< orphan*/  discarding_output; } ;
struct TYPE_11__ {TYPE_2__ state; TYPE_1__* buffer; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_9__ {int return_at_eof; } ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _cpp_read_logical_line_trad (TYPE_3__*) ; 
 TYPE_5__* cpp_get_token (TYPE_3__*) ; 
 int /*<<< orphan*/  traditional ; 

void
cpp_scan_nooutput (cpp_reader *pfile)
{
  /* Request a CPP_EOF token at the end of this file, rather than
     transparently continuing with the including file.  */
  pfile->buffer->return_at_eof = true;

  pfile->state.discarding_output++;
  pfile->state.prevent_expansion++;

  if (CPP_OPTION (pfile, traditional))
    while (_cpp_read_logical_line_trad (pfile))
      ;
  else
    while (cpp_get_token (pfile)->type != CPP_EOF)
      ;

  pfile->state.discarding_output--;
  pfile->state.prevent_expansion--;
}