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
struct TYPE_3__ {int (* get_user_language ) () ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;
typedef  enum retro_language { ____Placeholder_retro_language } retro_language ;

/* Variables and functions */
 int RETRO_LANGUAGE_ENGLISH ; 
 TYPE_1__* frontend_get_ptr () ; 
 int stub1 () ; 

enum retro_language frontend_driver_get_user_language(void)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();
   if (!frontend || !frontend->get_user_language)
      return RETRO_LANGUAGE_ENGLISH;
   return frontend->get_user_language();
}