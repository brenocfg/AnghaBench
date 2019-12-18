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
 int LABEL_ALIGN_LOG (int /*<<< orphan*/ ) ; 

int
label_to_alignment (rtx label)
{
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  return LABEL_ALIGN_LOG (label);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
}