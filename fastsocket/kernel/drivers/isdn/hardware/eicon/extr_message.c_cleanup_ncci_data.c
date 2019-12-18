#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
struct TYPE_9__ {scalar_t__ data_pending; size_t data_out; scalar_t__ data_ack_pending; scalar_t__ data_ack_out; TYPE_2__* DBuffer; } ;
struct TYPE_8__ {scalar_t__ Id; scalar_t__ data_sent_ptr; scalar_t__ appl; int /*<<< orphan*/  data_sent; TYPE_1__* adapter; } ;
struct TYPE_7__ {scalar_t__ P; } ;
struct TYPE_6__ {scalar_t__* ncci_plci; TYPE_4__* ncci; } ;
typedef  TYPE_3__ PLCI ;
typedef  TYPE_4__ NCCI ;

/* Variables and functions */
 size_t MAX_DATA_B3 ; 
 int /*<<< orphan*/  TransmitBufferFree (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cleanup_ncci_data (PLCI   *plci, word ncci)
{
  NCCI   *ncci_ptr;

  if (ncci && (plci->adapter->ncci_plci[ncci] == plci->Id))
  {
    ncci_ptr = &(plci->adapter->ncci[ncci]);
    if (plci->appl)
    {
      while (ncci_ptr->data_pending != 0)
      {
        if (!plci->data_sent || (ncci_ptr->DBuffer[ncci_ptr->data_out].P != plci->data_sent_ptr))
          TransmitBufferFree (plci->appl, ncci_ptr->DBuffer[ncci_ptr->data_out].P);
        (ncci_ptr->data_out)++;
        if (ncci_ptr->data_out == MAX_DATA_B3)
          ncci_ptr->data_out = 0;
        (ncci_ptr->data_pending)--;
      }
    }
    ncci_ptr->data_out = 0;
    ncci_ptr->data_pending = 0;
    ncci_ptr->data_ack_out = 0;
    ncci_ptr->data_ack_pending = 0;
  }
}