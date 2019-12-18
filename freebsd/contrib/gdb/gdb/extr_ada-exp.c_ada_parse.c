#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int _ada_parse () ; 
 int /*<<< orphan*/ * left_block_context ; 
 int /*<<< orphan*/  lexer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_qualifier ; 
 int /*<<< orphan*/  yyin ; 

int
ada_parse ()
{
  lexer_init (yyin);		/* (Re-)initialize lexer. */
  left_block_context = NULL;
  type_qualifier = NULL;
  
  return _ada_parse ();
}