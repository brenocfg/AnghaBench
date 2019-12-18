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
struct TYPE_2__ {int (* target_char_to_control_char ) (int /*<<< orphan*/ ,int,int*) ;int /*<<< orphan*/  target_char_to_control_char_baton; } ;

/* Variables and functions */
 TYPE_1__* current_target_charset ; 
 int stub1 (int /*<<< orphan*/ ,int,int*) ; 

int
target_char_to_control_char (int target_char, int *target_ctrl_char)
{
  return ((*current_target_charset->target_char_to_control_char)
          (current_target_charset->target_char_to_control_char_baton,
           target_char, target_ctrl_char));
}