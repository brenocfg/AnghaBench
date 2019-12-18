#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  falc; } ;
typedef  TYPE_1__ pc300ch_t ;
struct TYPE_6__ {int /*<<< orphan*/ * chan; } ;
typedef  TYPE_2__ pc300_t ;
struct TYPE_7__ {int /*<<< orphan*/  bec; } ;
typedef  TYPE_3__ falc_t ;

/* Variables and functions */

__attribute__((used)) static u16 falc_pattern_test_error(pc300_t * card, int ch)
{
	pc300ch_t *chan = (pc300ch_t *) & card->chan[ch];
	falc_t *pfalc = (falc_t *) & chan->falc;

	return (pfalc->bec);
}