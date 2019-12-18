#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int in_statement; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int IN_OMP_BLOCK ; 

__attribute__((used)) static unsigned
cp_parser_begin_omp_structured_block (cp_parser *parser)
{
  unsigned save = parser->in_statement;

  /* Only move the values to IN_OMP_BLOCK if they weren't false.
     This preserves the "not within loop or switch" style error messages
     for nonsense cases like
	void foo() {
	#pragma omp single
	  break;
	}
  */
  if (parser->in_statement)
    parser->in_statement = IN_OMP_BLOCK;

  return save;
}