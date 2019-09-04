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
struct TYPE_3__ {int /*<<< orphan*/  subrs; int /*<<< orphan*/  swap_table; int /*<<< orphan*/  glyph_names; int /*<<< orphan*/  charstrings; int /*<<< orphan*/  encoding_table; int /*<<< orphan*/  parser; } ;
typedef  int /*<<< orphan*/ * T1_Parser ;
typedef  TYPE_1__* T1_Loader ;

/* Variables and functions */
 int /*<<< orphan*/  T1_Finalize_Parser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T1_Release_Table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
  t1_done_loader( T1_Loader  loader )
  {
    T1_Parser  parser = &loader->parser;


    /* finalize tables */
    T1_Release_Table( &loader->encoding_table );
    T1_Release_Table( &loader->charstrings );
    T1_Release_Table( &loader->glyph_names );
    T1_Release_Table( &loader->swap_table );
    T1_Release_Table( &loader->subrs );

    /* finalize parser */
    T1_Finalize_Parser( parser );
  }