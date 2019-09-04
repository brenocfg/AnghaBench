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
typedef  TYPE_1__* ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_entry_bits_t ;
struct TYPE_3__ {int /*<<< orphan*/ * is_entropy; int /*<<< orphan*/  bool_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_BITS_ROLL_BITS ; 
 int /*<<< orphan*/  IS_ENTROPY_CNT ; 
 int /*<<< orphan*/  random_bool_gen_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ipc_entry_bits_t
ipc_space_get_rollpoint(
	ipc_space_t	space)
{
	return random_bool_gen_bits(
			&space->bool_gen,
			&space->is_entropy[0],
			IS_ENTROPY_CNT,
			IE_BITS_ROLL_BITS);
}