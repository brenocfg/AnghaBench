#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
union aux_ext {int /*<<< orphan*/  a_rndx; int /*<<< orphan*/  a_ti; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* swap_rndx_in ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ;int /*<<< orphan*/  (* swap_tir_in ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ;} ;
struct TYPE_15__ {int iauxBase; int /*<<< orphan*/  fBigendian; } ;
struct TYPE_14__ {int rfd; } ;
struct TYPE_13__ {scalar_t__ index; } ;
struct TYPE_12__ {scalar_t__ bt; } ;
struct TYPE_11__ {union aux_ext* external_aux; } ;
typedef  TYPE_1__ TIR ;
typedef  TYPE_2__ SYMR ;
typedef  TYPE_3__ RNDXR ;
typedef  TYPE_4__ FDR ;

/* Variables and functions */
 unsigned int AUX_GET_ISYM (int /*<<< orphan*/ ,union aux_ext*) ; 
 scalar_t__ btEnum ; 
 scalar_t__ btStruct ; 
 scalar_t__ btUnion ; 
 TYPE_10__* debug_info ; 
 TYPE_9__* debug_swap ; 
 scalar_t__ indexNil ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int
has_opaque_xref (FDR *fh, SYMR *sh)
{
  TIR tir;
  union aux_ext *ax;
  RNDXR rn[1];
  unsigned int rf;

  if (sh->index == indexNil)
    return 0;

  ax = debug_info->external_aux + fh->iauxBase + sh->index;
  (*debug_swap->swap_tir_in) (fh->fBigendian, &ax->a_ti, &tir);
  if (tir.bt != btStruct && tir.bt != btUnion && tir.bt != btEnum)
    return 0;

  ax++;
  (*debug_swap->swap_rndx_in) (fh->fBigendian, &ax->a_rndx, rn);
  if (rn->rfd == 0xfff)
    rf = AUX_GET_ISYM (fh->fBigendian, ax + 1);
  else
    rf = rn->rfd;
  if (rf != -1)
    return 0;
  return 1;
}