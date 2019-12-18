#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  cede_latency_hint; } ;
struct TYPE_5__ {TYPE_1__ fields; } ;
struct TYPE_6__ {TYPE_2__ gpr5_dword; } ;

/* Variables and functions */
 TYPE_3__* get_lppaca () ; 

__attribute__((used)) static inline u8 get_cede_latency_hint(void)
{
	return get_lppaca()->gpr5_dword.fields.cede_latency_hint;
}