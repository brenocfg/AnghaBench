#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cells; int /*<<< orphan*/  fpmask; } ;
typedef  TYPE_1__ qr_sampling_grid ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_sampling_grid_clear(qr_sampling_grid *_grid){
  free(_grid->fpmask);
  free(_grid->cells[0]);
}