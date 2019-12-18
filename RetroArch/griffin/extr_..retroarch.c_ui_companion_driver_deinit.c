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
struct TYPE_4__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ ui_companion_driver_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ qt_is_inited ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ui_companion ; 
 int /*<<< orphan*/ * ui_companion_data ; 
 TYPE_2__ ui_companion_qt ; 
 int /*<<< orphan*/ * ui_companion_qt_data ; 

__attribute__((used)) static void ui_companion_driver_deinit(void)
{
   const ui_companion_driver_t *ui = ui_companion;

   if (!ui)
      return;
   if (ui->deinit)
      ui->deinit(ui_companion_data);

#ifdef HAVE_QT
   if (qt_is_inited)
   {
      ui_companion_qt.deinit(ui_companion_qt_data);
      ui_companion_qt_data = NULL;
   }
#endif
   ui_companion_data = NULL;
}