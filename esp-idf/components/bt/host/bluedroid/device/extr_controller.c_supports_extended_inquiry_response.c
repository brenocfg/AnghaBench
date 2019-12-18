#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* features_classic; int /*<<< orphan*/  readable; } ;
struct TYPE_3__ {int /*<<< orphan*/  as_array; } ;

/* Variables and functions */
 int HCI_EXT_INQ_RSP_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__ controller_param ; 

__attribute__((used)) static bool supports_extended_inquiry_response(void)
{
    assert(controller_param.readable);
    return HCI_EXT_INQ_RSP_SUPPORTED(controller_param.features_classic[0].as_array);
}