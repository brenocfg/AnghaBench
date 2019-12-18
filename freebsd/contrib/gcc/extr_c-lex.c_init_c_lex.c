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
struct cpp_callbacks {int /*<<< orphan*/  undef; int /*<<< orphan*/  define; int /*<<< orphan*/  read_pch; int /*<<< orphan*/  valid_pch; int /*<<< orphan*/  def_pragma; int /*<<< orphan*/  ident; int /*<<< orphan*/  line_change; } ;
struct c_fileinfo {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ DINFO_LEVEL_VERBOSE ; 
 scalar_t__ DWARF2_DEBUG ; 
 scalar_t__ VMS_AND_DWARF2_DEBUG ; 
 int /*<<< orphan*/  body_time ; 
 int /*<<< orphan*/  c_common_read_pch ; 
 int /*<<< orphan*/  c_common_valid_pch ; 
 int /*<<< orphan*/  cb_def_pragma ; 
 int /*<<< orphan*/  cb_define ; 
 int /*<<< orphan*/  cb_ident ; 
 int /*<<< orphan*/  cb_line_change ; 
 int /*<<< orphan*/  cb_undef ; 
 struct cpp_callbacks* cpp_get_callbacks (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_info_level ; 
 scalar_t__ flag_detailed_statistics ; 
 struct c_fileinfo* get_fileinfo (char*) ; 
 int /*<<< orphan*/  get_run_time () ; 
 scalar_t__ header_time ; 
 int /*<<< orphan*/  parse_in ; 
 scalar_t__ write_symbols ; 

void
init_c_lex (void)
{
  struct cpp_callbacks *cb;
  struct c_fileinfo *toplevel;

  /* The get_fileinfo data structure must be initialized before
     cpp_read_main_file is called.  */
  toplevel = get_fileinfo ("<top level>");
  if (flag_detailed_statistics)
    {
      header_time = 0;
      body_time = get_run_time ();
      toplevel->time = body_time;
    }

  cb = cpp_get_callbacks (parse_in);

  cb->line_change = cb_line_change;
  cb->ident = cb_ident;
  cb->def_pragma = cb_def_pragma;
  cb->valid_pch = c_common_valid_pch;
  cb->read_pch = c_common_read_pch;

  /* Set the debug callbacks if we can use them.  */
  if (debug_info_level == DINFO_LEVEL_VERBOSE
      && (write_symbols == DWARF2_DEBUG
	  || write_symbols == VMS_AND_DWARF2_DEBUG))
    {
      cb->define = cb_define;
      cb->undef = cb_undef;
    }
}