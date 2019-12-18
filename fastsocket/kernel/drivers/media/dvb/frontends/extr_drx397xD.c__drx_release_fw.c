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
struct drx397xD_state {int dummy; } ;
typedef  enum fw_ix { ____Placeholder_fw_ix } fw_ix ;
struct TYPE_2__ {scalar_t__ file; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 TYPE_1__* fw ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 

__attribute__((used)) static void _drx_release_fw(struct drx397xD_state *s, enum fw_ix ix)
{
	memset(&fw[ix].data[0], 0, sizeof(fw[0].data));
	if (fw[ix].file)
		release_firmware(fw[ix].file);
}