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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  gen_rtx_CODE_LABEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_num ; 

rtx
gen_label_rtx (void)
{
  return gen_rtx_CODE_LABEL (VOIDmode, 0, NULL_RTX, NULL_RTX,
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
			     NULL, label_num++, NULL, 0);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
}