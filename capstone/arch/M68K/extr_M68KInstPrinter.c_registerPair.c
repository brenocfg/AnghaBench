#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t reg_0; size_t reg_1; } ;
struct TYPE_5__ {TYPE_1__ reg_pair; } ;
typedef  TYPE_2__ cs_m68k_op ;
typedef  int /*<<< orphan*/  SStream ;

/* Variables and functions */
 size_t M68K_REG_D0 ; 
 int /*<<< orphan*/  SStream_concat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_reg_names ; 

__attribute__((used)) static void registerPair(SStream* O, const cs_m68k_op* op)
{
	SStream_concat(O, "%s:%s", s_reg_names[M68K_REG_D0 + op->reg_pair.reg_0],
			s_reg_names[M68K_REG_D0 + op->reg_pair.reg_1]);
}