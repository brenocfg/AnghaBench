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
typedef  int /*<<< orphan*/  tdtrav_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  t_tdesc; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 int tdtraverse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tdtrav_plain(tdesc_t *this, tdtrav_data_t *tdtd)
{
	return (tdtraverse(this->t_tdesc, &this->t_tdesc, tdtd));
}