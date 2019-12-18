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
typedef  int /*<<< orphan*/  ProtobufCMessage ;
typedef  int /*<<< orphan*/  ProtobufCAllocator ;
typedef  TYPE_2__ CmdSetConfig ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmd_set_config__descriptor ; 
 int /*<<< orphan*/  protobuf_c_message_free_unpacked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void   cmd_set_config__free_unpacked
                     (CmdSetConfig *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &cmd_set_config__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}