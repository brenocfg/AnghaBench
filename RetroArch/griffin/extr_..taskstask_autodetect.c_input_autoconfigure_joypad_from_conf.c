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
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  int /*<<< orphan*/  config_file_t ;
typedef  int /*<<< orphan*/  autoconfig_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_autoconfigure_joypad_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int input_autoconfigure_joypad_try_from_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int input_autoconfigure_joypad_from_conf(
      config_file_t *conf, autoconfig_params_t *params, retro_task_t *task)
{
   int ret = input_autoconfigure_joypad_try_from_conf(conf,
         params);

   if (ret)
      input_autoconfigure_joypad_add(conf, params, task);

   config_file_free(conf);

   return ret;
}