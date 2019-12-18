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
struct block {int arg_index; int /*<<< orphan*/  text_len; int /*<<< orphan*/ * text; } ;
struct TYPE_4__ {int /*<<< orphan*/ * text; } ;
struct TYPE_5__ {scalar_t__ paramc; int /*<<< orphan*/  count; TYPE_1__ exp; int /*<<< orphan*/ ** params; scalar_t__ fun_like; } ;
typedef  TYPE_2__ cpp_macro ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODE_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NODE_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uchar *
_cpp_copy_replacement_text (const cpp_macro *macro, uchar *dest)
{
  if (macro->fun_like && (macro->paramc != 0))
    {
      const uchar *exp;

      for (exp = macro->exp.text;;)
	{
	  struct block *b = (struct block *) exp;
	  cpp_hashnode *param;

	  memcpy (dest, b->text, b->text_len);
	  dest += b->text_len;
	  if (b->arg_index == 0)
	    break;
	  param = macro->params[b->arg_index - 1];
	  memcpy (dest, NODE_NAME (param), NODE_LEN (param));
	  dest += NODE_LEN (param);
	  exp += BLOCK_LEN (b->text_len);
	}
    }
  else
    {
      memcpy (dest, macro->exp.text, macro->count);
      dest += macro->count;
    }

  return dest;
}