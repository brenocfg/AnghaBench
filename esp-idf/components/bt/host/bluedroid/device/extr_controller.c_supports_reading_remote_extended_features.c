#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  supported_commands; int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 int HCI_READ_REMOTE_EXT_FEATURES_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ controller_param ; 

__attribute__((used)) static bool supports_reading_remote_extended_features(void)
{
    assert(controller_param.readable);
    return HCI_READ_REMOTE_EXT_FEATURES_SUPPORTED(controller_param.supported_commands);
}