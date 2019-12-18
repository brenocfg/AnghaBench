#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  la_case_sensitivity; int /*<<< orphan*/  la_type_check; int /*<<< orphan*/  la_range_check; } ;

/* Variables and functions */
 scalar_t__ case_mode ; 
 scalar_t__ case_mode_auto ; 
 int /*<<< orphan*/  case_sensitivity ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  range_check ; 
 scalar_t__ range_mode ; 
 scalar_t__ range_mode_auto ; 
 int /*<<< orphan*/  set_case_str () ; 
 int /*<<< orphan*/  set_range_str () ; 
 int /*<<< orphan*/  set_type_str () ; 
 int /*<<< orphan*/  type_check ; 
 scalar_t__ type_mode ; 
 scalar_t__ type_mode_auto ; 

__attribute__((used)) static void
set_type_range_case (void)
{

  if (range_mode == range_mode_auto)
    range_check = current_language->la_range_check;

  if (type_mode == type_mode_auto)
    type_check = current_language->la_type_check;

  if (case_mode == case_mode_auto)
    case_sensitivity = current_language->la_case_sensitivity;

  set_type_str ();
  set_range_str ();
  set_case_str ();
}