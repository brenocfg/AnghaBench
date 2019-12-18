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
typedef  int /*<<< orphan*/  gca_pad_t ;

/* Variables and functions */

__attribute__((used)) static const char *wiiu_gca_get_name(void *data)
{
   gca_pad_t *pad = (gca_pad_t *)data;

   return "GameCube Controller";
}