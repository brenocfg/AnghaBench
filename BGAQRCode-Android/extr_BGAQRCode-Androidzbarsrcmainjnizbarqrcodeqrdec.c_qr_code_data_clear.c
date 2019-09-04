#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nentries; TYPE_5__* entries; } ;
typedef  TYPE_3__ qr_code_data ;
struct TYPE_6__ {TYPE_5__* buf; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_9__ {TYPE_2__ payload; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ QR_MODE_HAS_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 

__attribute__((used)) static void qr_code_data_clear(qr_code_data *_qrdata){
  int i;
  for(i=0;i<_qrdata->nentries;i++){
    if(QR_MODE_HAS_DATA(_qrdata->entries[i].mode)){
      free(_qrdata->entries[i].payload.data.buf);
    }
  }
  free(_qrdata->entries);
}