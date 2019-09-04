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
struct TYPE_4__ {int nqrdata; scalar_t__ qrdata; } ;
typedef  TYPE_1__ qr_code_data_list ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  qr_code_data_clear (scalar_t__) ; 
 int /*<<< orphan*/  qr_code_data_list_init (TYPE_1__*) ; 

void qr_code_data_list_clear(qr_code_data_list *_qrlist){
  int i;
  for(i=0;i<_qrlist->nqrdata;i++)qr_code_data_clear(_qrlist->qrdata+i);
  free(_qrlist->qrdata);
  qr_code_data_list_init(_qrlist);
}