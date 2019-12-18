#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * descriptor; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ SessionResp0 ;
typedef  int /*<<< orphan*/  ProtobufCMessage ;
typedef  int /*<<< orphan*/  ProtobufCAllocator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  protobuf_c_message_free_unpacked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_resp0__descriptor ; 

void   session_resp0__free_unpacked
                     (SessionResp0 *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &session_resp0__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}