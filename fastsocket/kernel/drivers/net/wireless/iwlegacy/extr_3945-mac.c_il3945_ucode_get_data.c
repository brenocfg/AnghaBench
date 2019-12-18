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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ data; } ;
struct il_ucode_header {TYPE_1__ v1; } ;

/* Variables and functions */

__attribute__((used)) static u8 *
il3945_ucode_get_data(const struct il_ucode_header *ucode)
{
	return (u8 *) ucode->v1.data;
}