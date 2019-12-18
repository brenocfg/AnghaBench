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
struct TYPE_4__ {int pc; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 unsigned int peek_imm_8 (TYPE_1__*) ; 

__attribute__((used)) static unsigned int read_imm_8(m68k_info *info)  { const unsigned int value = peek_imm_8(info);  (info)->pc+=2; return value; }