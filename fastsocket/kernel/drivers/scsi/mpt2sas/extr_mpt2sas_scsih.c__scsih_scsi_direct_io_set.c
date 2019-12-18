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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct MPT2SAS_ADAPTER {TYPE_1__* scsi_lookup; } ;
struct TYPE_2__ {int /*<<< orphan*/  direct_io; } ;

/* Variables and functions */

__attribute__((used)) static inline void
_scsih_scsi_direct_io_set(struct MPT2SAS_ADAPTER *ioc, u16 smid, u8 direct_io)
{
	ioc->scsi_lookup[smid - 1].direct_io = direct_io;
}