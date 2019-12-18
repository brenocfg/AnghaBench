#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxHandle_t ;
typedef  int /*<<< orphan*/  menuframework_s ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  (* callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
 int QMF_SILENT ; 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 int /*<<< orphan*/  menu_move_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

sfxHandle_t Menu_ActivateItem( menuframework_s *s, menucommon_s* item ) {
	if ( item->callback ) {
		item->callback( item, QM_ACTIVATED );
		if( !( item->flags & QMF_SILENT ) ) {
			return menu_move_sound;
		}
	}

	return 0;
}