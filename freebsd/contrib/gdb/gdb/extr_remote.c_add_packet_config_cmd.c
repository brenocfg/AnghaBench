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
struct packet_config {char* name; char* title; int /*<<< orphan*/  detect; int /*<<< orphan*/  support; } ;
struct cmd_list_element {int dummy; } ;
typedef  int /*<<< orphan*/  cmd_sfunc_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_BOOLEAN_AUTO ; 
 int /*<<< orphan*/  PACKET_SUPPORT_UNKNOWN ; 
 int /*<<< orphan*/  add_alias_cmd (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_list_element**) ; 
 int /*<<< orphan*/  add_setshow_auto_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,...) ; 

__attribute__((used)) static void
add_packet_config_cmd (struct packet_config *config,
		       char *name,
		       char *title,
		       cmd_sfunc_ftype *set_func,
		       cmd_sfunc_ftype *show_func,
		       struct cmd_list_element **set_remote_list,
		       struct cmd_list_element **show_remote_list,
		       int legacy)
{
  struct cmd_list_element *set_cmd;
  struct cmd_list_element *show_cmd;
  char *set_doc;
  char *show_doc;
  char *cmd_name;
  config->name = name;
  config->title = title;
  config->detect = AUTO_BOOLEAN_AUTO;
  config->support = PACKET_SUPPORT_UNKNOWN;
  xasprintf (&set_doc, "Set use of remote protocol `%s' (%s) packet",
	     name, title);
  xasprintf (&show_doc, "Show current use of remote protocol `%s' (%s) packet",
	     name, title);
  /* set/show TITLE-packet {auto,on,off} */
  xasprintf (&cmd_name, "%s-packet", title);
  add_setshow_auto_boolean_cmd (cmd_name, class_obscure,
				&config->detect, set_doc, show_doc,
				set_func, show_func,
				set_remote_list, show_remote_list);
  /* set/show remote NAME-packet {auto,on,off} -- legacy */
  if (legacy)
    {
      char *legacy_name;
      xasprintf (&legacy_name, "%s-packet", name);
      add_alias_cmd (legacy_name, cmd_name, class_obscure, 0,
		     set_remote_list);
      add_alias_cmd (legacy_name, cmd_name, class_obscure, 0,
		     show_remote_list);
    }
}