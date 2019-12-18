#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_5__ {unsigned int len; char* text; } ;
struct TYPE_6__ {TYPE_1__ str; } ;
struct TYPE_7__ {int type; TYPE_2__ val; } ;
typedef  TYPE_3__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 char* _cpp_unaligned_alloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 

__attribute__((used)) static void
create_literal (cpp_reader *pfile, cpp_token *token, const uchar *base,
		unsigned int len, enum cpp_ttype type)
{
  uchar *dest = _cpp_unaligned_alloc (pfile, len + 1);

  memcpy (dest, base, len);
  dest[len] = '\0';
  token->type = type;
  token->val.str.len = len;
  token->val.str.text = dest;
}