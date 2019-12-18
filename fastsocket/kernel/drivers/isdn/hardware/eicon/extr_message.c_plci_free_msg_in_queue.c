#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_9__ {scalar_t__ command; int length; } ;
struct TYPE_7__ {scalar_t__ Data; } ;
struct TYPE_8__ {TYPE_1__ data_b3_req; } ;
struct TYPE_11__ {TYPE_3__ header; TYPE_2__ info; } ;
struct TYPE_10__ {size_t msg_in_read_pos; size_t msg_in_write_pos; size_t msg_in_wrap_pos; scalar_t__ msg_in_queue; scalar_t__ appl; } ;
typedef  TYPE_4__ PLCI ;
typedef  TYPE_5__ CAPI_MSG ;

/* Variables and functions */
 int MSG_IN_OVERHEAD ; 
 void* MSG_IN_QUEUE_SIZE ; 
 int /*<<< orphan*/  TransmitBufferFree (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ _DATA_B3_R ; 

__attribute__((used)) static void plci_free_msg_in_queue (PLCI   *plci)
{
  word i;

  if (plci->appl)
  {
    i = plci->msg_in_read_pos;
    while (i != plci->msg_in_write_pos)
    {
      if (i == plci->msg_in_wrap_pos)
        i = 0;
      if (((CAPI_MSG   *)(&((byte   *)(plci->msg_in_queue))[i]))->header.command == _DATA_B3_R)
      {

        TransmitBufferFree (plci->appl,
          (byte *)(long)(((CAPI_MSG *)(&((byte *)(plci->msg_in_queue))[i]))->info.data_b3_req.Data));

      }

      i += (((CAPI_MSG   *)(&((byte   *)(plci->msg_in_queue))[i]))->header.length +
        MSG_IN_OVERHEAD + 3) & 0xfffc;

    }
  }
  plci->msg_in_write_pos = MSG_IN_QUEUE_SIZE;
  plci->msg_in_read_pos = MSG_IN_QUEUE_SIZE;
  plci->msg_in_wrap_pos = MSG_IN_QUEUE_SIZE;
}