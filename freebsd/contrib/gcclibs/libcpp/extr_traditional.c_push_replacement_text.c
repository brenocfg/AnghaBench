#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_9__ {char* text; } ;
struct TYPE_10__ {int used; int traditional; size_t count; TYPE_2__ exp; } ;
typedef  TYPE_3__ cpp_macro ;
struct TYPE_8__ {TYPE_3__* macro; } ;
struct TYPE_11__ {int flags; TYPE_1__ value; } ;
typedef  TYPE_4__ cpp_hashnode ;

/* Variables and functions */
 int NODE_BUILTIN ; 
 char* _cpp_builtin_macro_text (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  _cpp_push_text_context (int /*<<< orphan*/ *,TYPE_4__*,char const*,size_t) ; 
 char* _cpp_unaligned_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t ustrlen (char const*) ; 

__attribute__((used)) static void
push_replacement_text (cpp_reader *pfile, cpp_hashnode *node)
{
  size_t len;
  const uchar *text;
  uchar *buf;

  if (node->flags & NODE_BUILTIN)
    {
      text = _cpp_builtin_macro_text (pfile, node);
      len = ustrlen (text);
      buf = _cpp_unaligned_alloc (pfile, len + 1);
      memcpy (buf, text, len);
      buf[len]='\n';
      text = buf;
    }
  else
    {
      cpp_macro *macro = node->value.macro;
      macro->used = 1;
      text = macro->exp.text;
      macro->traditional = 1;
      len = macro->count;
    }

  _cpp_push_text_context (pfile, node, text, len);
}