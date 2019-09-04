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
struct TYPE_3__ {scalar_t__ cqrdata; scalar_t__ nqrdata; int /*<<< orphan*/ * qrdata; } ;
typedef  TYPE_1__ qr_code_data_list ;

/* Variables and functions */

void qr_code_data_list_init(qr_code_data_list *_qrlist){
  _qrlist->qrdata=NULL;
  _qrlist->nqrdata=_qrlist->cqrdata=0;
}