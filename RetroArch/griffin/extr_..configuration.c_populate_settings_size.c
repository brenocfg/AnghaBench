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
struct config_size_setting {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rewind_buffer_size; } ;
struct TYPE_5__ {TYPE_1__ sizes; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_REWIND_BUFFER_SIZE ; 
 int /*<<< orphan*/  SETTING_SIZE (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static struct config_size_setting *populate_settings_size(settings_t *settings, int *size)
{
   unsigned count                     = 0;
   struct config_size_setting  *tmp   = (struct config_size_setting*)calloc((*size + 1), sizeof(struct config_size_setting));

   if (!tmp)
      return NULL;

   SETTING_SIZE("rewind_buffer_size",           &settings->sizes.rewind_buffer_size, true, DEFAULT_REWIND_BUFFER_SIZE, false);

   *size = count;

   return tmp;
}