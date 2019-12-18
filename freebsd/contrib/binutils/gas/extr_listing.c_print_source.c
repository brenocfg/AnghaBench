#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hll_line; } ;
typedef  TYPE_1__ list_info_type ;
struct TYPE_8__ {scalar_t__ linenum; char* filename; int /*<<< orphan*/  at_end; } ;
typedef  TYPE_2__ file_info_type ;

/* Variables and functions */
 char* buffer_line (TYPE_2__*,char*,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  list_file ; 
 int /*<<< orphan*/  listing_page (TYPE_1__*) ; 
 int /*<<< orphan*/  on_page ; 

__attribute__((used)) static void
print_source (file_info_type *current_file, list_info_type *list,
	      char *buffer, unsigned int width)
{
  if (!current_file->at_end)
    {
      while (current_file->linenum < list->hll_line
	     && !current_file->at_end)
	{
	  char *p = buffer_line (current_file, buffer, width);

	  fprintf (list_file, "%4u:%-13s **** %s\n", current_file->linenum,
		   current_file->filename, p);
	  on_page++;
	  listing_page (list);
	}
    }
}