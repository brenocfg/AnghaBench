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
 int /*<<< orphan*/  QImode ; 
 int thumb_base_register_rtx_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) inline static int
thumb_index_register_rtx_p (rtx x, int strict_p)
{
  return thumb_base_register_rtx_p (x, QImode, strict_p);
}