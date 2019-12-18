#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ want_prefix; } ;
struct TYPE_6__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_LOG_ERROR ; 
 TYPE_2__ usrvcsm_log_category ; 
 int /*<<< orphan*/  vcos_log_register (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_set_level (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcsm_mutex ; 

__attribute__((used)) static void vcsm_init_once(void)
{
   vcos_mutex_create(&vcsm_mutex, VCOS_FUNCTION);
   vcos_log_set_level(&usrvcsm_log_category, VCOS_LOG_ERROR);
   usrvcsm_log_category.flags.want_prefix = 0;
   vcos_log_register( "usrvcsm", &usrvcsm_log_category );
}