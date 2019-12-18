#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Scsi_Host {scalar_t__ io_port; } ;

/* Variables and functions */
 char in_8 (scalar_t__) ; 

__attribute__((used)) static __inline__ char macscsi_read(struct Scsi_Host *instance, int reg)
{
  return in_8(instance->io_port + (reg<<4));
}