#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
struct TYPE_4__ {int localap_enable; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_LOCALAP_SWITCHING_OFF ; 
 int /*<<< orphan*/  MSG_WIFI_SCAN_COMPLETE ; 
 int /*<<< orphan*/  RARCH_FILETYPE_UNSET ; 
 TYPE_2__* config_get_ptr () ; 
 scalar_t__ connmanctl_tether_status () ; 
 int /*<<< orphan*/  connmanctl_tether_toggle (int,char*,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ lines ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_append (scalar_t__,char*,union string_list_elem_attr) ; 
 scalar_t__ string_list_new () ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void connmanctl_scan(void)
{
   char line[512];
   union string_list_elem_attr attr;
   FILE *serv_file                  = NULL;
   settings_t *settings             = config_get_ptr();

   attr.i = RARCH_FILETYPE_UNSET;
   if (lines)
      free(lines);
   lines = string_list_new();

   if (connmanctl_tether_status())
   {
      runloop_msg_queue_push(msg_hash_to_str(MSG_LOCALAP_SWITCHING_OFF),
            1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT,
            MESSAGE_QUEUE_CATEGORY_INFO);
      settings->bools.localap_enable = false;
      connmanctl_tether_toggle(false, "", "");
   }

   pclose(popen("connmanctl enable wifi", "r"));

   pclose(popen("connmanctl scan wifi", "r"));

   runloop_msg_queue_push(msg_hash_to_str(MSG_WIFI_SCAN_COMPLETE),
         1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT,
         MESSAGE_QUEUE_CATEGORY_INFO);

   serv_file = popen("connmanctl services", "r");
   while (fgets (line, 512, serv_file) != NULL)
   {
      size_t len = strlen(line);
      if (len > 0 && line[len-1] == '\n')
         line[--len] = '\0';

      string_list_append(lines, line, attr);
   }
   pclose(serv_file);
}