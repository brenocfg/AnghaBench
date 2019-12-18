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
struct TYPE_2__ {int alias; int align; int /*<<< orphan*/  expr; scalar_t__ size; scalar_t__ offset; } ;
typedef  TYPE_1__ mem_attrs ;
typedef  int hashval_t ;

/* Variables and functions */
 int INTVAL (scalar_t__) ; 
 scalar_t__ iterative_hash_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
mem_attrs_htab_hash (const void *x)
{
  mem_attrs *p = (mem_attrs *) x;

  return (p->alias ^ (p->align * 1000)
	  ^ ((p->offset ? INTVAL (p->offset) : 0) * 50000)
	  ^ ((p->size ? INTVAL (p->size) : 0) * 2500000)
	  ^ (size_t) iterative_hash_expr (p->expr, 0));
}