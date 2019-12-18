#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_22__ {scalar_t__ enum_idx; int /*<<< orphan*/  action_sublabel_ident; int /*<<< orphan*/  action_label_ident; int /*<<< orphan*/  action_get_title_ident; int /*<<< orphan*/  action_get_value_ident; int /*<<< orphan*/  action_refresh_ident; int /*<<< orphan*/  action_deferred_push_ident; int /*<<< orphan*/  action_right_ident; int /*<<< orphan*/  action_left_ident; int /*<<< orphan*/  action_down_ident; int /*<<< orphan*/  action_up_ident; int /*<<< orphan*/  action_content_list_switch_ident; int /*<<< orphan*/  action_info_ident; int /*<<< orphan*/  action_select_ident; int /*<<< orphan*/  action_start_ident; int /*<<< orphan*/  action_scan_ident; int /*<<< orphan*/  action_cancel_ident; int /*<<< orphan*/  action_ok_ident; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;
struct TYPE_23__ {char const* path; char const* label; unsigned int type; size_t idx; int /*<<< orphan*/  label_hash; TYPE_1__* cbs; } ;
typedef  TYPE_2__ menu_ctx_bind_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 scalar_t__ MSG_UNKNOWN ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_BIND_INIT ; 
 int /*<<< orphan*/  menu_cbs_init_bind_cancel (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_content_list_switch (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_deferred_push (TYPE_1__*,char const*,char const*,unsigned int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_down (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_get_string_representation (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_info (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_label (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_left (TYPE_1__*,char const*,char const*,unsigned int,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_ok (TYPE_1__*,char const*,char const*,unsigned int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_refresh (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_right (TYPE_1__*,char const*,char const*,unsigned int,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_scan (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_select (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_start (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_sublabel (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_title (TYPE_1__*,char const*,char const*,unsigned int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_cbs_init_bind_up (TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_cbs_init_log (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_hash_calculate (char const*) ; 
 int /*<<< orphan*/  msg_hash_to_str (scalar_t__) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

void menu_cbs_init(void *data,
      menu_file_list_cbs_t *cbs,
      const char *path, const char *label,
      unsigned type, size_t idx)
{
   menu_ctx_bind_t bind_info;
   const char *repr_label        = NULL;
   const char *menu_label        = NULL;
   uint32_t label_hash           = 0;
   uint32_t menu_label_hash      = 0;
   enum msg_hash_enums enum_idx  = MSG_UNKNOWN;
   file_list_t *list             = (file_list_t*)data;
   if (!list)
      return;

   menu_entries_get_last_stack(NULL, &menu_label, NULL, &enum_idx, NULL);

   if (!label || !menu_label)
      return;

   label_hash      = msg_hash_calculate(label);
   menu_label_hash = msg_hash_calculate(menu_label);

#ifdef DEBUG_LOG
   RARCH_LOG("\n");
#endif

   repr_label = (!string_is_empty(label)) ? label : path;

#ifdef DEBUG_LOG
   if (cbs && cbs->enum_idx != MSG_UNKNOWN)
      RARCH_LOG("\t\t\tenum_idx %d [%s]\n", cbs->enum_idx, msg_hash_to_str(cbs->enum_idx));
#endif

   /* It will try to find a corresponding callback function inside
    * menu_cbs_ok.c, then map this callback to the entry. */
   menu_cbs_init_bind_ok(cbs, path, label, type, idx, label_hash, menu_label_hash);

   menu_cbs_init_log(repr_label, "OK", cbs->action_ok_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_cancel.c, then map this callback to the entry. */
   menu_cbs_init_bind_cancel(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "CANCEL", cbs->action_cancel_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_scan.c, then map this callback to the entry. */
   menu_cbs_init_bind_scan(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "SCAN", cbs->action_scan_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_start.c, then map this callback to the entry. */
   menu_cbs_init_bind_start(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "START", cbs->action_start_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_select.c, then map this callback to the entry. */
   menu_cbs_init_bind_select(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "SELECT", cbs->action_select_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_info.c, then map this callback to the entry. */
   menu_cbs_init_bind_info(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "INFO", cbs->action_info_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_bind_content_list_switch.c, then map this callback to the entry. */
   menu_cbs_init_bind_content_list_switch(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "CONTENT SWITCH", cbs->action_content_list_switch_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_up.c, then map this callback to the entry. */
   menu_cbs_init_bind_up(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "UP", cbs->action_up_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_down.c, then map this callback to the entry. */
   menu_cbs_init_bind_down(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "DOWN", cbs->action_down_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_left.c, then map this callback to the entry. */
   menu_cbs_init_bind_left(cbs, path, label, type, idx, menu_label, label_hash);

   menu_cbs_init_log(repr_label, "LEFT", cbs->action_left_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_right.c, then map this callback to the entry. */
   menu_cbs_init_bind_right(cbs, path, label, type, idx, menu_label, label_hash);

   menu_cbs_init_log(repr_label, "RIGHT", cbs->action_right_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_deferred_push.c, then map this callback to the entry. */
   menu_cbs_init_bind_deferred_push(cbs, path, label, type, idx, label_hash);

   menu_cbs_init_log(repr_label, "DEFERRED PUSH", cbs->action_deferred_push_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_refresh.c, then map this callback to the entry. */
   menu_cbs_init_bind_refresh(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "REFRESH", cbs->action_refresh_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_get_string_representation.c, then map this callback to the entry. */
   menu_cbs_init_bind_get_string_representation(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "GET VALUE", cbs->action_get_value_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_title.c, then map this callback to the entry. */
   menu_cbs_init_bind_title(cbs, path, label, type, idx, label_hash);

   menu_cbs_init_log(repr_label, "GET TITLE", cbs->action_get_title_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_label.c, then map this callback to the entry. */
   menu_cbs_init_bind_label(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "LABEL", cbs->action_label_ident);

   /* It will try to find a corresponding callback function inside
    * menu_cbs_sublabel.c, then map this callback to the entry. */
   menu_cbs_init_bind_sublabel(cbs, path, label, type, idx);

   menu_cbs_init_log(repr_label, "SUBLABEL", cbs->action_sublabel_ident);

   bind_info.cbs             = cbs;
   bind_info.path            = path;
   bind_info.label           = label;
   bind_info.type            = type;
   bind_info.idx             = idx;
   bind_info.label_hash      = label_hash;

   menu_driver_ctl(RARCH_MENU_CTL_BIND_INIT, &bind_info);
}