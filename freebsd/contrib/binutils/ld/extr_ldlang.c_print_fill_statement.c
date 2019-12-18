#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* fill; } ;
typedef  TYPE_2__ lang_fill_statement_type ;
struct TYPE_7__ {int /*<<< orphan*/  map_file; } ;
struct TYPE_5__ {unsigned char* data; size_t size; } ;

/* Variables and functions */
 TYPE_4__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_fill_statement (lang_fill_statement_type *fill)
{
  size_t size;
  unsigned char *p;
  fputs (" FILL mask 0x", config.map_file);
  for (p = fill->fill->data, size = fill->fill->size; size != 0; p++, size--)
    fprintf (config.map_file, "%02x", *p);
  fputs ("\n", config.map_file);
}