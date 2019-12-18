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

/* Variables and functions */
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  obj_elf_text (int) ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
s_score_text (int ignore)
{
  obj_elf_text (ignore);
  record_alignment (now_seg, 2);
}