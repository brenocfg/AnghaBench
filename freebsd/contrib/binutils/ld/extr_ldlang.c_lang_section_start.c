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
typedef  int /*<<< orphan*/  segment_type ;
struct TYPE_3__ {char const* section_name; int /*<<< orphan*/  const* segment; int /*<<< orphan*/ * address; } ;
typedef  TYPE_1__ lang_address_statement_type ;
typedef  int /*<<< orphan*/  etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  lang_address_statement ; 
 TYPE_1__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_ptr ; 

void
lang_section_start (const char *name, etree_type *address,
		    const segment_type *segment)
{
  lang_address_statement_type *ad;

  ad = new_stat (lang_address_statement, stat_ptr);
  ad->section_name = name;
  ad->address = address;
  ad->segment = segment;
}