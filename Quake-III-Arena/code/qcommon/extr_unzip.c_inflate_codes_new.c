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
typedef  int /*<<< orphan*/  z_streamp ;
typedef  scalar_t__ uInt ;
struct inflate_codes_state {int dummy; } ;
typedef  int /*<<< orphan*/  inflate_huft ;
struct TYPE_4__ {int /*<<< orphan*/ * dtree; int /*<<< orphan*/ * ltree; void* dbits; void* lbits; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ inflate_codes_statef ;
typedef  void* Byte ;

/* Variables and functions */
 int /*<<< orphan*/  START ; 
 int /*<<< orphan*/  Tracev (char*) ; 
 scalar_t__ ZALLOC (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* Z_NULL ; 

inflate_codes_statef *inflate_codes_new(uInt bl, uInt bd, inflate_huft *tl, inflate_huft *td, z_streamp z)
{
  inflate_codes_statef *c;

  if ((c = (inflate_codes_statef *)
       ZALLOC(z,1,sizeof(struct inflate_codes_state))) != Z_NULL)
  {
    c->mode = START;
    c->lbits = (Byte)bl;
    c->dbits = (Byte)bd;
    c->ltree = tl;
    c->dtree = td;
    Tracev(("inflate:       codes new\n"));
  }
  return c;
}