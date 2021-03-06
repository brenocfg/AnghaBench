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
typedef  TYPE_2__ CmdGetPropertyCount ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmd_get_property_count__descriptor ; 
 size_t protobuf_c_message_get_packed_size (int /*<<< orphan*/  const*) ; 

size_t cmd_get_property_count__get_packed_size
                     (const CmdGetPropertyCount *message)
{
  assert(message->base.descriptor == &cmd_get_property_count__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}