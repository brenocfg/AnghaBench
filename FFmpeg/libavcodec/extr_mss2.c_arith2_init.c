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
struct TYPE_4__ {int /*<<< orphan*/ * gB; } ;
struct TYPE_5__ {int high; int /*<<< orphan*/  get_number; int /*<<< orphan*/  get_model_sym; TYPE_1__ gbc; scalar_t__ overread; int /*<<< orphan*/  value; scalar_t__ low; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ ArithCoder ;

/* Variables and functions */
 int /*<<< orphan*/  arith2_get_model_sym ; 
 int /*<<< orphan*/  arith2_get_number ; 
 int /*<<< orphan*/  bytestream2_get_be24 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arith2_init(ArithCoder *c, GetByteContext *gB)
{
    c->low           = 0;
    c->high          = 0xFFFFFF;
    c->value         = bytestream2_get_be24(gB);
    c->overread      = 0;
    c->gbc.gB        = gB;
    c->get_model_sym = arith2_get_model_sym;
    c->get_number    = arith2_get_number;
}