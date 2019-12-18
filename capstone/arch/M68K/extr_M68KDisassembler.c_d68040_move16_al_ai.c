#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ir; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68040_PLUS ; 
 int M68K_AM_ABSOLUTE_DATA_LONG ; 
 int M68K_AM_REG_DIRECT_ADDR ; 
 int /*<<< orphan*/  build_move16 (TYPE_1__*,int*,int*) ; 
 int read_imm_32 (TYPE_1__*) ; 

__attribute__((used)) static void d68040_move16_al_ai(m68k_info *info)
{
	int data[] = { read_imm_32(info), info->ir & 7 };
	int modes[] = { M68K_AM_ABSOLUTE_DATA_LONG, M68K_AM_REG_DIRECT_ADDR };

	LIMIT_CPU_TYPES(info, M68040_PLUS);

	build_move16(info, data, modes);
}