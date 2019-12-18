#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mark; int /*<<< orphan*/  filter; int /*<<< orphan*/  mdct_win; TYPE_1__* band; int /*<<< orphan*/  mdct; } ;
typedef  TYPE_2__ envelope_lookup ;
struct TYPE_5__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int VE_BANDS ; 
 int /*<<< orphan*/  _ogg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdct_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void _ve_envelope_clear(envelope_lookup *e){
  int i;
  mdct_clear(&e->mdct);
  for(i=0;i<VE_BANDS;i++)
    _ogg_free(e->band[i].window);
  _ogg_free(e->mdct_win);
  _ogg_free(e->filter);
  _ogg_free(e->mark);
  memset(e,0,sizeof(*e));
}