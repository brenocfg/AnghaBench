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
 scalar_t__ CPP_PADDING ; 
 TYPE_1__* cpp_get_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const cpp_token *
get_a_token (cpp_reader *pfile)
{
  for (;;)
    {
      const cpp_token *result = cpp_get_token (pfile);
      if (result->type != CPP_PADDING)
	return result;
    }
}