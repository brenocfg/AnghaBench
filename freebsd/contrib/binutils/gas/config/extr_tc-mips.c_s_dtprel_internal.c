#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ X_op; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_7__ {int fr_literal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_MIPS_TLS_DTPREL32 ; 
 int /*<<< orphan*/  BFD_RELOC_MIPS_TLS_DTPREL64 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_2__*,char*,size_t,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* frag_more (size_t) ; 
 TYPE_2__* frag_now ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
s_dtprel_internal (size_t bytes)
{
  expressionS ex;
  char *p;

  expression (&ex);

  if (ex.X_op != O_symbol)
    {
      as_bad (_("Unsupported use of %s"), (bytes == 8
					   ? ".dtpreldword"
					   : ".dtprelword"));
      ignore_rest_of_line ();
    }

  p = frag_more (bytes);
  md_number_to_chars (p, 0, bytes);
  fix_new_exp (frag_now, p - frag_now->fr_literal, bytes, &ex, FALSE,
	       (bytes == 8
		? BFD_RELOC_MIPS_TLS_DTPREL64
		: BFD_RELOC_MIPS_TLS_DTPREL32));

  demand_empty_rest_of_line ();
}