#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; scalar_t__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ symbol_info ;
struct TYPE_9__ {int /*<<< orphan*/  name; TYPE_1__* section; scalar_t__ value; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_7__ {scalar_t__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_decode_symclass (TYPE_3__*) ; 
 scalar_t__ bfd_is_undefined_symclass (int /*<<< orphan*/ ) ; 

void
bfd_symbol_info (asymbol *symbol, symbol_info *ret)
{
  ret->type = bfd_decode_symclass (symbol);

  if (bfd_is_undefined_symclass (ret->type))
    ret->value = 0;
  else
    ret->value = symbol->value + symbol->section->vma;

  ret->name = symbol->name;
}