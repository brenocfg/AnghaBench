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
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 scalar_t__ CPP_STRING ; 
 scalar_t__ CPP_WSTRING ; 
 TYPE_1__* get_token_no_padding (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const cpp_token *
get__Pragma_string (cpp_reader *pfile)
{
  const cpp_token *string;

  if (get_token_no_padding (pfile)->type != CPP_OPEN_PAREN)
    return NULL;

  string = get_token_no_padding (pfile);
  if (string->type != CPP_STRING && string->type != CPP_WSTRING)
    return NULL;

  if (get_token_no_padding (pfile)->type != CPP_CLOSE_PAREN)
    return NULL;

  return string;
}