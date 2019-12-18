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
typedef  int /*<<< orphan*/  uchar ;
struct block {int arg_index; scalar_t__ text_len; } ;
struct TYPE_4__ {int /*<<< orphan*/ * text; } ;
struct TYPE_5__ {scalar_t__ paramc; size_t count; int /*<<< orphan*/ * params; TYPE_1__ exp; scalar_t__ fun_like; } ;
typedef  TYPE_2__ cpp_macro ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_LEN (scalar_t__) ; 
 scalar_t__ NODE_LEN (int /*<<< orphan*/ ) ; 

size_t
_cpp_replacement_text_len (const cpp_macro *macro)
{
  size_t len;

  if (macro->fun_like && (macro->paramc != 0))
    {
      const uchar *exp;

      len = 0;
      for (exp = macro->exp.text;;)
	{
	  struct block *b = (struct block *) exp;

	  len += b->text_len;
	  if (b->arg_index == 0)
	    break;
	  len += NODE_LEN (macro->params[b->arg_index - 1]);
	  exp += BLOCK_LEN (b->text_len);
	}
    }
  else
    len = macro->count;
  
  return len;
}