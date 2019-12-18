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
struct TYPE_3__ {int /*<<< orphan*/  parser; } ;
typedef  int /*<<< orphan*/  CID_Parser ;
typedef  TYPE_1__ CID_Loader ;

/* Variables and functions */
 int /*<<< orphan*/  cid_parser_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static  void
  cid_done_loader( CID_Loader*  loader )
  {
    CID_Parser*  parser = &loader->parser;


    /* finalize parser */
    cid_parser_done( parser );
  }