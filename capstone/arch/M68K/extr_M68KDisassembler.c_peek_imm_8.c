#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 int m68k_read_safe_16 (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int peek_imm_8(const m68k_info *info)  { return (m68k_read_safe_16((info), (info)->pc)&0xff); }