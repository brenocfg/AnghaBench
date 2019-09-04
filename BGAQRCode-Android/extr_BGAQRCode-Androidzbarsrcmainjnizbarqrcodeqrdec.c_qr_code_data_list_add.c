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
struct TYPE_3__ {int nqrdata; int cqrdata; int /*<<< orphan*/ * qrdata; } ;
typedef  TYPE_1__ qr_code_data_list ;
typedef  int /*<<< orphan*/  qr_code_data ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qr_code_data_list_add(qr_code_data_list *_qrlist,
 qr_code_data *_qrdata){
  if(_qrlist->nqrdata>=_qrlist->cqrdata){
    _qrlist->cqrdata=_qrlist->cqrdata<<1|1;
    _qrlist->qrdata=(qr_code_data *)realloc(_qrlist->qrdata,
     _qrlist->cqrdata*sizeof(*_qrlist->qrdata));
  }
  memcpy(_qrlist->qrdata+_qrlist->nqrdata++,_qrdata,sizeof(*_qrdata));
}