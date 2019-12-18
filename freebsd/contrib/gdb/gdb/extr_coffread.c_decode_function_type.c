#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ l; } ;
struct TYPE_4__ {TYPE_1__ x_tagndx; } ;
union internal_auxent {TYPE_2__ x_sym; } ;
struct type {int dummy; } ;
struct coff_symbol {scalar_t__ c_naux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECREF (unsigned int) ; 
 struct type* decode_type (struct coff_symbol*,int /*<<< orphan*/ ,union internal_auxent*) ; 

__attribute__((used)) static struct type *
decode_function_type (struct coff_symbol *cs, unsigned int c_type,
		      union internal_auxent *aux)
{
  if (aux->x_sym.x_tagndx.l == 0)
    cs->c_naux = 0;		/* auxent refers to function, not base type */

  return decode_type (cs, DECREF (c_type), aux);
}