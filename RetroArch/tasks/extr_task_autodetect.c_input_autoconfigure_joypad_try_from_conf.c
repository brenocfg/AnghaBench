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
typedef  int /*<<< orphan*/  input_driver ;
typedef  int /*<<< orphan*/  ident ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_3__ {int vid; int pid; char* name; } ;
typedef  TYPE_1__ autoconfig_params_t ;

/* Variables and functions */
 int BLISSBOX_PID ; 
 int BLISSBOX_VID ; 
 int /*<<< orphan*/  config_get_array (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ config_get_int (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

__attribute__((used)) static int input_autoconfigure_joypad_try_from_conf(config_file_t *conf,
      autoconfig_params_t *params)
{
   char ident[256];
   char input_driver[32];
   int tmp_int                = 0;
   int              input_vid = 0;
   int              input_pid = 0;
   int                  score = 0;

   ident[0] = input_driver[0] = '\0';

   config_get_array(conf, "input_device", ident, sizeof(ident));
   config_get_array(conf, "input_driver", input_driver, sizeof(input_driver));

   if (config_get_int  (conf, "input_vendor_id", &tmp_int))
      input_vid = tmp_int;

   if (config_get_int  (conf, "input_product_id", &tmp_int))
      input_pid = tmp_int;

   if (params->vid == BLISSBOX_VID)
      input_pid = BLISSBOX_PID;

   /* Check for VID/PID */
   if (     (params->vid == input_vid)
         && (params->pid == input_pid)
         && (params->vid != 0)
         && (params->pid != 0)
         && (params->vid != BLISSBOX_VID)
         && (params->pid != BLISSBOX_PID))
      score += 3;

   /* Check for name match */
   if (!string_is_empty(params->name)
         && !string_is_empty(ident)
         && string_is_equal(ident, params->name))
      score += 2;

   return score;
}