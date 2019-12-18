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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * descriptor; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ RespGetPropertyCount ;
typedef  int /*<<< orphan*/  ProtobufCMessage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t protobuf_c_message_pack (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_get_property_count__descriptor ; 

size_t resp_get_property_count__pack
                     (const RespGetPropertyCount *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &resp_get_property_count__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}